import java.util.ArrayList;

public class Main {
    public static int getValueAtIndex(int index, ArrayList<Integer> idSequence) {
        return idSequence.get(index);
    }

    public static void main(String[] args) {
        ArrayList<Integer> idSequence = new ArrayList<>();
        // Example of adding elements to the list
        idSequence.add(10);
        idSequence.add(20);
        idSequence.add(30);

        int index = 1; // Example index
        System.out.println(getValueAtIndex(index, idSequence));
    }
}