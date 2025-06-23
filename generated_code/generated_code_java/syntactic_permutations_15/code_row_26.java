import java.util.*;
    
    public class Main {
      public static void main(String[] args) {
        String[] arr = {"Java", "Python", "Ruby"};
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter an index:");
        int index = scanner.nextInt();
        
        return arr[index];
      }
    }