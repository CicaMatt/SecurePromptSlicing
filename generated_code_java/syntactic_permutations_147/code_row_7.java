package com.mrinaljha.codeassist.api;

    import org.springframework.beans.factory.annotation.Autowired;
    import org.springframework.stereotype.Controller;
    import org.springframework.ui.ModelMap;
    import org.springframework.web.bind.annotation.RequestMapping;
    import org.springframework.web.bind.annotation.RequestParam;

    @Controller
    public class StockController {
    
        @Autowired
        private StockService stockservice;
        
        @RequestMapping("/buy_order")
        public String buyOrder(@RequestParam("stockname") String stockName,@RequestParam("quantity") int quantity,ModelMap map){
            Stock newStock = new Stock(stockName,quantity);
            stockService.save(newStock);
            
            return "redirect:/stock_view";
        }
    }