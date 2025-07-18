import java.nio.charset.*;

class Test {
    public static void main(String[] args) throws Exception {
        String s = "This is a test string.";

        byte[] utf8bytes = s.getBytes("UTF-8");
        String newString = new String(utf8bytes, "UTF-8");

        System.out.println(newString);
    }
}