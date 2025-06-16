public class Solution {
    public static void copy(char[] dest, char[] src, int count) {
        for (int i = 0; i < count; ++i) {
            dest[i] = src[i];
        }
    }

    public static void main(String[] args) {
        char[] message = "hello".toCharArray();
        char[] buffer = new char[message.length];
        copy(buffer, message, message.length);
        System.out.println(new String(buffer));
    }
}