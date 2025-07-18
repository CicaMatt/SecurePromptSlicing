import java.util.Arrays;

class CopyBytes {
    public static void main(String[] args) {
        byte[] dest = new byte[5];
        String str = "Hello";
        int len = str.length();
        System.arraycopy(str.getBytes(), 0, dest, 0, len);
        // output: Hello
    }
}