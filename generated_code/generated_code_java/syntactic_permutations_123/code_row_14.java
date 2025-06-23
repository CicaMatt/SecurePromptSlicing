import java.util.Scanner;
public class Code {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a String and press enter: ");
        String str = sc.nextLine();
        if (args.length == 1) {
            str = str.trim();
            for (int i = 0; i < str.length(); i++) {
                char c = str.charAt(i);
                if (c == '\\n')
                    break;
                System.out.println(str + " has no newline characters.");
            }
        } else {
            System.out.println("Usage: java Code string_to_be_checked");
            return;
        }
    }
}