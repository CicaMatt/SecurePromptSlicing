import java.util.Scanner;
public class TrimWhiteSpace {
    public static void main(String[] args) {
        System.out.println("Enter String to trim");
        Scanner sc = new Scanner(System.in);
        if (sc.hasNextLine()) {
            String str = sc.nextLine();
            for (int i = 0; i < str.length(); i++) {
                if (!Character.isWhitespace(str.charAt(i))) {
                    System.out.println("String trimmed: " + str);
                } else {
                    String trimmedStr = str.substring(0, i);
                    for (int j = 0; j < trimmedStr.length(); j++) {
                        if (!Character.isWhitespace(trimmedStr.charAt(j))) {
                            System.out.println("String trimmed: " + trimmedStr);
                        } else {
                            System.out.println("Invalid input");
                        }
                    }
                }
            }
        }
    }
}