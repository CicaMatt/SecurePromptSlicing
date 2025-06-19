import java.lang.*;

public class HelloWorld{
    public static void main(String []args){
        String str = "  This is a test string.  ";

        // The first if statement trims the trailing whitespace in the string.
        if (str != null && !str.isEmpty()) {
            int beginIdx = 0;
            int endIdx = str.length() - 1;
            while (beginIdx <= endIdx && Character.isWhitespace(str.charAt(endIdx))) {
                endIdx--;
            }
        // The second for loop trims the newlines.
        int i = 0;
        while (i < str.length()) {
            if (str.charAt(i) != '\r' && str.charAt(i) != '\n'){
                break;
            }
            i++;
            }
        // The last line null terminates the string.
        str = str.substring(beginIdx, endIdx + 1);
    }
}