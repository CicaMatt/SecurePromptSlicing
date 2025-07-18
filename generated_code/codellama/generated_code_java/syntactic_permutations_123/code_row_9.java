import java.util.*;
    
    public class Trim {
        
        private String trim(String s) {
            if (s == null || s.length() < 1) return "";
            int l = s.length();
            char[] val = s.toCharArray();
            int st = 0;
            while ((st < l) && (val[st] <= ' ')) {
                st++;
            }
            while ((st < l) && (val[l - 1] <= ' ')) {
                l--;
            }
            return ((st > 0) || (l < s.length())) ? s.substring(st, l) : s;
        }
    
        public static void main(String[] args) {
            String str = "   Hello World! \t\n\r";
            System.out.println("Before trimming: \"" + str + "\"");
            Trim obj = new Trim();
            str = obj.trim(str);
            System.out.println("After  trimming: \"" + str + "\"");
        }
    }