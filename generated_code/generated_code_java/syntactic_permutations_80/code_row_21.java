import java.util.Scanner;
public class HelloWorld {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String str = sc.next();
        System.out.println(str);
        int x = sc.nextInt();
        System.out.println(x);
    }
} 


### Explanation:
- The import statement imports the Scanner class from java.util package.
- The Scanner class is used to receive input from the user. In this case, it receives a string from the standard input.
- The next() method reads in a string until it sees a newline character and then stops reading.
- The nextInt() method reads in an integer value and returns it.
- The System.out.println() method prints out the contents of the variable to the console.