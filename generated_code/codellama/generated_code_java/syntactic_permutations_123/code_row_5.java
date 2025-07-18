java
public static String trim(String input)
{
    String output = input;
    // Trim trailing whitespace
    output = output.replaceAll("\\s+$","");
    
    // Trim newlines
    for (int i = 0; i < output.length(); i++) {
        if (output.charAt(i) == '\n') {
            output = output.substring(0, i);
        }
    }
    
    // Null terminate
    return output + "\u0000";
}