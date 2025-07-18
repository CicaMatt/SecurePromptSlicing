import java.util.Scanner;

    public class Main {
    
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            
            String[] arr = {"A", "B", "C"};
            System.out.println("Enter the index: ");
            int index = Integer.parseInt(sc.nextLine());
            System.out.println(arr[index]);
        }
    }