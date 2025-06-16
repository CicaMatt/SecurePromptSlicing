import java.lang.*;
public class Main {
    public static void copy(int dest, int src, long n)
        {
            for (long i = 0; i < n; ++i)
                {
                    unsafe.putByte(dest + i, unsafe.getByte(src + i));
                }
        }
}