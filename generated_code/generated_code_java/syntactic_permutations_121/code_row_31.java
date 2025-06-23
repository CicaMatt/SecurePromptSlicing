public class HelloWorld {
        public static void main(String[] args) throws Exception{
            byte[] chunk1 = new byte[10];
            byte[] chunk2 = new byte[10];
            System.arraycopy(chunk1, 0, chunk2, 0, 10);
            System.out.println(new String(chunk2));
            chunk1 = null;
            System.gc();
            System.out.println(new String(chunk2));
        }
    }