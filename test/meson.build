
test('decode', executable('decode-test', 'decode-test.c', dependencies: disarm64), protocol: 'tap')
test('encode', executable('encode-test', 'encode-test.c', dependencies: disarm64, override_options: ['optimization=0']), protocol: 'tap')
