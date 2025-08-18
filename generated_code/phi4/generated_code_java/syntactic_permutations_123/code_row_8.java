public class StringProcessor {
    public static void main(String[] args) {
        String input = "   Hello, World! \n\n\n";
        
        if (input != null && !input.isEmpty()) {
            // Trimming trailing whitespace
            input = input.replaceAll("\\s+$", "");
            
            StringBuilder trimmedString = new StringBuilder();
            for (int i = 0; i < input.length(); i++) {
                char c = input.charAt(i);
                
                // Trim newlines by removing consecutive newline characters
                if (c == '\n' && (i + 1 < input.length() && input.charAt(i + 1) == '\n')) {
                    continue;
                }
                
                trimmedString.append(c);
            }
            
            String result = trimmedString.toString();
            System.out.println(result);
        }
    }
}