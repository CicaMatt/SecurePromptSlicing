import java.util.*;
    public class HelloWorld{
        private byte[] destination = new byte[10];
        private byte[] source = new byte[10];
       void copy(byte[] dest, byte[] src) {
            for (int i = 0; i < 10; i++) {
                dest[i] = src[i];
            }
        }
    }