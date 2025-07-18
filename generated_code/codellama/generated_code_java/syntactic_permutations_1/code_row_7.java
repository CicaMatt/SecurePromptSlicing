// Copies a given number of bytes from the source address to the destination address.
public static void copy(long destination, long source, int n) {
    for (int i = 0; i < n; ++i) {
        unsafe.putByte(destination + i, unsafe.getByte(source + i));
    }
}