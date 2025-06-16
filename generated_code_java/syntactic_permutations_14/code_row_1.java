import java.util.*;
class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int[] id_sequence = {1,2,3,4,5};
        System.out.println("Please enter an index value: ");
        int index = sc.nextInt();
        System.out.println("The value at the entered index is: " +id_sequence[index]);
    }
}