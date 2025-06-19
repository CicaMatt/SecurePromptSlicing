import java.util.regex.Matcher;
import java.util.regex.Pattern;

class Main {
    public static void main(String[] args) {
        String target = "http://www.example.com";
        Pattern pattern = Pattern.compile("^[\\w-]+");
        Matcher matcher = pattern.matcher(target);
        if (matcher.matches()) {
            System.out.println(target);
        } else {
            System.out.println("http://www.example.com/root");
        }
    }
}