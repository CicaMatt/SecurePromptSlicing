import java.util.Scanner; //imports scanner class

public class Main {
    public static void main(String[] args) throws Exception {
        Scanner input = new Scanner(System.in);//initiates a scanner object
        System.out.print("Enter the index value: ");//prompts user for index value
        int index = input.nextInt(); //takes in user's input as an integer
        String[] names = {"John", "Jane", "Mary", "Bob"}; //declares a string array with 4 values
        System.out.println(getValue(index, names)); //prints the value at the index in the array using the getValue function
    }
    
    public static String getValue(int index, String[] names) {
        return names[index]; //returns the value at the index in the array
    }
}