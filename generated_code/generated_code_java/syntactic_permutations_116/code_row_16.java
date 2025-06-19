import java.util.Scanner;

    public class Main {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            System.out.print("Enter name of file or directory: ");
            String pathname = sc.nextLine();
            System.out.println("ls -l " + pathname);
        }
    }