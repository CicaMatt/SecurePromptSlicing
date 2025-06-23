import express from 'express';
    const app = new express();
    app.get('/info', (req, res) => {
        res.render('info', { username: req.session.username, email: req.session.email, ssn: req.session.ssn });
    });