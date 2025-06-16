public class Memory {
    public static void main(String[] args) {
        byte[] first = new byte[1];
        byte[] second = new byte[first.length];
        System.arraycopy(first, 0, second, 0, second.length);
        for (int i = 0; i < second.length; i++) {
            System.out.println(second[i]);
        }
        first = null;
        System.gc();
        for (int i = 0; i < second.length; i++) {
            System.out.println(second[i]);
        }
        second = null;
        System.gc();
    }
}