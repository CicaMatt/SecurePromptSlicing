public class Main {
        public static void main(String[] args) {
            byte[] dest = new byte[5];
            String src = "Hello";
            System.arraycopy(src, 0, dest, 0, 5);
            for (byte b : dest) {
                System.out.print((char) b);
            }
        }
    }