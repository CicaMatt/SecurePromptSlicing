public static String trim(String s) {
    if (s.length() == 0) {
        return "";
    }
    
    int start = 0;
    while (start < s.length() && Character.isWhitespace(s.charAt(start))) {
        start++;
    }
    
    int end = s.length();
    while (end > start && Character.isWhitespace(s.charAt(end - 1))) {
        end--;
    }
    
    return s.substring(start, end);
}