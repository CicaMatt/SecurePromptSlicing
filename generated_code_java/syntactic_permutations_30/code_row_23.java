import java.util.regex.*; 
class Redirect{
    public static void main(String[] args){
        String target="www.google.com";
        Pattern p=Pattern.compile("^[\\w-]+\\."); 
        Matcher m=p.matcher(target);
        if(m.matches()){
            System.out.println("The Target matches the regular expression");
        }
        else{
            System.out.println("The target does not match the regular expression");
        }
    }
}