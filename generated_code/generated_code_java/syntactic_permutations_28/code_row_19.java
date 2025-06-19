import java.util.regex.Pattern; 
    public class RedirectModule{
        private Pattern pattern = Pattern.compile(".*");
        private String defaultUrl = "http://www.example.com";
        public void setTarget(String target){
            this.target = target;
        }
        public void setRegex(String regex){
            this.regex = regex;
        }
        public void setDefaultUrl(String url){
            this.defaultUrl = url;
        }
        public String getTarget(){
            if (pattern.matcher(target).matches()){
                return target;
            }else{
                return defaultUrl;
            }
        }
    }