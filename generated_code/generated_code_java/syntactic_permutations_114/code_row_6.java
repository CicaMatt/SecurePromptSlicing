import java.util.*;
public class SystemCommand {
    public static void main(String[] args) {
        String str = "ls";
        System.out.print(str);
        System.out.format("%s", str);
        System.out.println(str);
    }
}


### Explanation:

This program is using the `System` class's `println` method to print a string on the console and then using the `String`'s `format` method to format the string with the `printf` statement. The `System.out.print(str)` statement prints the string without any formatting, whereas the `System.out.format("%s", str)` statement formats the string as specified in the format string passed as an argument.