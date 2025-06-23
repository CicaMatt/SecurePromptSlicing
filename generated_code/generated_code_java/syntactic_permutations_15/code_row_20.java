import java.util.*;

public class IdIndex {
    public static void main(String[] args) {
        String[] idSequence = new String[] {"A", "B", "C"};
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an index value:");
        int index = scanner.nextInt();
        String idAtIndex = idSequence[index];
        System.out.println("The ID at that index is " + idAtIndex);
    }
}