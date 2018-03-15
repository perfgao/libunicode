local ffi = require "ffi"

local str_gmatch = string.gmatch
local str_match = string.match

ffi.cdef[[
int get_encoded_len(const char *src);
int encode(const char *src, char *dst);

int get_decode_len(const char *src, int opt);
int decode(const char *src, char *dst);
]]

local lib, loaded

local function loadlib()
    if loaded then
        return true
    end

    -- no load

    local libname = "libunicode.so"
    local so_path, path

    for k in str_gmatch(package.cpath, "[^;]+") do
        so_path = str_match(k, "(.*/)")
        if so_path then
            so_path = so_path .. libname

            local f, err = io.open(so_path)
            if f then
                io.close(f)
                path = so_path
                break
            end
        end
    end

    if not path then
        return false
    end

    lib = ffi.load(path)
    if not lib then
        return false
    end

    loaded = true

    return true
end


local function utf8_to_unicode(srcstr)
    if loadlib() ~= true then
        return nil, "cannot load libunicode.so"
    end

    if type(srcstr) ~= 'string' then
        return nil, 'invaild'
    end

    if srcstr == "" then
        return ""
    end

    local len = lib.get_encoded_len(srcstr)
    if len < 0 then
        return nil, "get len error"
    end

    local dst = ffi.new("char[?]", len)

    lib.encode(srcstr, dst)

    return ffi.string(dst)
end

local function unicode_to_utf8(srcstr, opt)
    if loadlib() ~= true then
        return nil, "cannot load libunicode.so"
    end

    if type(srcstr) ~= 'string' then
        return nil, "invaild"
    end

    local len = opt and lib.get_decode_len(srcstr, opt) or #srcstr
    if len < 0 then
        return nil, "get decode failed"
    end

    local dst = ffi.new("char[?]", len)

    lib.decode(srcstr, dst)

    return ffi.string(dst)
end


local _M = {
    _VERSION = '0.01',
    encode = utf8_to_unicode,
    decode = unicode_to_utf8,
}

return _M
