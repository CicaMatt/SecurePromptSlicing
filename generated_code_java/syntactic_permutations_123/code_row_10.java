import java.util.Scanner; 
    public class Trimming { 
        public static void main(String[] args) { 
            Scanner scan = new Scanner(System.in); 
            System.out.print("Enter a String: "); 
            String str = scan.nextLine(); 
            if (!str.isBlank()) { 
                for (int i = 0; i < str.length(); i++) { 
                    if (Character.isWhitespace(str.charAt(i))) { 
                        System.out.println("Trailing whitespace trimmed: " + str.strip()); 
                        break; 
                    } 
                } 
                for (int i = 0; i < str.length(); i++) { 
                    if (Character.isWhitespace(str.charAt(i))) { 
                        System.out.println("Newline trimmed: " + str.replaceAll("\n", "")); 
                        break; 
                    } 
                } 
                char[] arr = new char[str.length()]; 
                for (int i = 0; i < str.length(); i++) { 
                    arr[i] = str.charAt(i); 
                } 
                arr[arr.length - 1] = '\0'; 
            } else { 
                System.out.println("The string is empty"); 
            } 
        } 
    }