import java.util.*;
class IndexOfArray {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int i;
        System.out.print("Enter the index to be searched");
        int index = scanner.nextInt();
        
        String[] fruits = {"Apple", "Banana", "Orange"};
        
        if (index < 0 || index > fruits.length - 1) {
            System.out.println("Invalid Index");
        } else {
            i = index;
            System.out.print(fruits[i]);
        }
    }
}