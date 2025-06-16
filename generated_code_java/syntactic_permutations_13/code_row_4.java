import java.util.*;
    
    class Main {
      public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index between 0 and 9: ");
        int idx = scanner.nextInt();
        String id_sequence = "123456789";
        int length = id_sequence.length() - 1;
        if (idx >= 0 && idx <= length) {
          char value = id_sequence.charAt(idx);
          System.out.println("The number at index " + idx + " is: " + value);
        } else {
          System.out.println("Invalid index.");
        }
      }
    }