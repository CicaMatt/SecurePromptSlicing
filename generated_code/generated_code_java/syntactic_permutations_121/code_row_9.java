public class HelloWorld {
        static void main(String[] args) {
            int size1 = 256;
            int size2 = 256;
            byte[] array1 = new byte[size1];
            byte[] array2 = new byte[size2];
            System.arraycopy(array1, 0, array2, 0, Math.min(size1, size2));
            for (int i = 0; i < array2.length; i++) {
                System.out.print((char) array2[i]);
            }
        }
    }