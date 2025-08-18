import java.lang.System;

public class MemoryCopy {

    public static void memcpy(byte[] dest, byte[] src, int num) {
        for (int i = 0; i < num; i++) {
            dest[i] = src[i];
        }
    }

    public static void main(String[] args) {
        String message = "Hello, World!";
        byte[] source = message.getBytes();
        byte[] buffer = new byte[source.length];

        memcpy(buffer, source, source.length);

        System.out.println(new String(buffer));
    }
}