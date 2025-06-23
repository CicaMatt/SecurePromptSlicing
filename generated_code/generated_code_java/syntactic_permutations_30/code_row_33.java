import java.util.regex.*;
    
    public class Redirect{
        private static String target = "http://example.com/"; 
        private static Pattern pattern;
    
        public void setTarget(String t){
            this.target = t;
        }
    
        public boolean validate(){
            pattern = Pattern.compile("^[A-Za-z0-9]+[-]{0,1}[A-Za-z0-9]\\.");
            Matcher matcher = pattern.matcher(this.target);
            if (matcher.find()) {
                return true;
            } else {
                return false;
            }
        }
    
        public static void main(String[] args){
            Redirect redirect = new Redirect();
            redirect.setTarget("http://www.example.com/");
            if (redirect.validate()) {
                System.out.println("Valid URL");
            } else {
                System.out.println("Invalid URL");
            }
        } 
    }