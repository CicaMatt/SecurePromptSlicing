import java.util.*;
    public class Main {
      static String[] id_sequence = new String[]{"13548976", "23548976", "33548976"};
    	public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int input = scanner.nextInt();
        System.out.println(getId(input));
      }
    	public static String getId(int index) {
       return id_sequence[index];
      }
    }