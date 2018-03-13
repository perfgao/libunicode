local ffi = require "ffi"

local lib = ffi.load("./libunicode.so")

if not lib then
    return nil, "load failed"
end

ffi.cdef[[
int get_encoded_len(const char *src);
int encode(const char *src, char *dst);

int get_decode_len(const char *src, int opt);
int decode(const char *src, char *dst);
]]

local function utf8_to_unicode(srcstr)
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
