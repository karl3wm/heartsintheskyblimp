git submodule update --init --recursive --filter=blob:none arduinogpio/pigpio
mkdir build_pigpio
cd build_pigpio
cmake ../../arduinogpio/pigpio -DCMAKE_INSTALL_PREFIX="$PREFIX" -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_FLAGS='-Wno-deprecated-non-prototype -include strings.h -include netinet/in.h -Dpthread_cancel\(th\)=ENOSYS -DPTHREAD_CANCEL_DISABLE=1 -Dpthread_setcancelstate\(st,o_st\)=\(\(void\)\(st\),o_st?*\(int*\)\(o_st\)=PTHREAD_CANCEL_DISABLE:0,ENOSYS\)' &&
make &&
make install && cp -va "$PREFIX"/man/. -va "$PREFIX"/share/man/. && rm -rf "$PREFIX"/man

echo ''
echo "pigs h for help"
echo ''
