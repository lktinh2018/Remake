var jwt = require("jsonwebtoken");

module.exports = function(app) {

  app.get("/", function(req, res) {
    res.render("index.ejs");
  });

  app.get("/addmember.ejs", function(req, res) {
    res.render("addmember.ejs");
  });

  app.get("/main.ejs", function(req, res) {
    var cookies = req.cookies;
    var token = cookies.token;
  	if (token) {
		    jwt.verify(token, "superSecret", function(err, decoded) {
    			if (err) {
    				return res.json({success: false, message: 'Failed to authenticate token.'});
    			} else {
            res.render("main.ejs");
    			}
  		});
  	} else {
  		return res.status(403).send({
  			success: false,
  			message: 'No token provided.'
  		});
  	}
  });

  app.get('/clearcookie', function(req,res){
     var keys = Object.keys(req.cookies);
     console.log(keys);
     for(var i in keys)
      res.clearCookie(keys[i]);
     res.send('Cookie deleted');
  });

  app.listen(80, function() {
    console.log("Web server listen on port 80");
  });

}
