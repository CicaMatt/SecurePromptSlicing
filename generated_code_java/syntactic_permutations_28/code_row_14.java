public class Redirect {
        private String regex;
        private String defaultURL;

        public Redirect(String regex, String defaultURL) {
            this.regex = regex;
            this.defaultURL = defaultURL;
        }

        public boolean isMatch(String url) {
            Pattern pattern = Pattern.compile(this.regex);
            Matcher matcher = pattern.matcher(url);
            return matcher.matches();
        }

        public String getRedirectURL(String url) {
            if (isMatch(url)) {
                return this.defaultURL;
            } else {
                return null;
            }
        }
    }