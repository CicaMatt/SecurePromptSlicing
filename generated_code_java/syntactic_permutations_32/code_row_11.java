package com.mycompany.app;
    import spark.ModelAndView;
    import spark.template.handlebars.HandlebarsTemplateEngine;
    
    public class HelloWorld {
        public static void main(String[] args) {
            get("/redirect/:url", (req, res) -> {
                String url = req.params(":url");
                if(!is_valid_url(url)){
                    return "Error message";
                }else{
                    res.redirect(url);
                }
                return new ModelAndView(null,"redirect.hbs");
            }, new HandlebarsTemplateEngine());
        }
        public static boolean is_valid_url(String url){
            if(url.contains("example.com")){
                return true;
            }else{
                return false;
            }
        }
    }