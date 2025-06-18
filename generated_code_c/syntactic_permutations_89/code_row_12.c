// Importing libraries
     import express from 'express'
     import bodyParser from 'body-parser'
     
    // Creating an instance of express
     const app = express()
     
     app.use(bodyParser.urlencoded({ extended: true }))
     
     app.listen(5000, () => {
       console.log('Server running at http://localhost:5000/')
     })
     
    // Defining a function to calculate the price of a product
     const calculatePrice = (code, quantity) => {
       const products = [
         { code: '123ABC', name: 'Laptop', price: 1500 },
         { code: '456DEF', name: 'Mobile phone', price: 500 },
         { code: '789GHI', name: 'Headphones', price: 80 }
       ]
     
       let totalPrice = 0
     
       products.forEach(product => {
         if (code === product.code) {
           totalPrice = quantity * product.price
           return totalPrice
         }
       })
       
       return totalPrice
     }
     
    // Defining a route to handle the request for calculating price
     app.get('/price', (req, res) => {
       const code = req.query.code
       const quantity = req.query.quantity
     
       console.log(calculatePrice(code, quantity))
       
       res.end()
     })