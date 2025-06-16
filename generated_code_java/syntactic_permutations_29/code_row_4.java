import spark.ModelAndView;
    import spark.template.handlebars.HandlebarsTemplateEngine;
    
    public class Hello {
        public static void main(String[] args) {
            String reg = "example.com";
            if (args[0].equals(reg)) {
                System.out.println("Matched");
            } else {
                System.out.println("Not matched");
            }
        }
    }