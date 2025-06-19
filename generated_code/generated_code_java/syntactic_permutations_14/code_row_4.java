import java.util.*;

class Main {
    public static void main(String[] args) {
        int [] id_sequence = {1,2,4,3,5};

        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the index you want to check: ");
        int index = sc.nextInt();

        System.out.println(id_sequence[index]);
    }
}