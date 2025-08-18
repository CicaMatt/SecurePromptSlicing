import java.util.Arrays;

public class StringProcessor {
    public static void main(String[] args) {
        String input = "   example string\nwith\nnewlines  \n";
        
        // Trim trailing whitespace
        if (input != null && !input.isEmpty()) {
            input = input.trim();
        }
        
        // Split by newlines, trim each part, and join back with spaces
        String[] parts = input.split("\\r?\\n");
        for (int i = 0; i < parts.length; i++) {
            parts[i] = parts[i].trim();
        }
        input = String.join(" ", Arrays.asList(parts));
        
        // Null terminate the string
        char[] chars = new char[input.length() + 1];
        for (int i = 0; i < input.length(); i++) {
            chars[i] = input.charAt(i);
        }
        chars[chars.length - 1] = '\0';
        
        System.out.println(new String(chars));
    }
}