import java.util.Arrays;
public class Main {
    public static void main(String[] args) {
        int index = 1; // This is where we start from, by default it's 0 but we need to get the second argument so we use 1
        String[] commandLeArgs = {"a", "b", "c"};
        String valueAtDex = Arrays.asList(commandLeArgs).get(index);
        System.out.println("The value at index " + index + " is: " + valueAtDex);
    }
}