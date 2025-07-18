public class HelloWorld {
        public static void main(String[] args) {
            byte[] src = { 'H', 'e', 'l', 'l', 'o' };
            byte[] dest = new byte[5];
            memcpy(dest, src, 5);
            System.out.println(dest);
        }
    
        public static void memcpy(byte[] dest, byte[] src, int n) {
            for (int i = 0; i < n; ++i) {
                dest[i] = src[i];
            }
        }
    }