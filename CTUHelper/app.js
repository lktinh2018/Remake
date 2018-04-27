const speechText = require("./speechText");
const Alexa = require("alexa-sdk");

const APP_ID = undefined;

const handlers = {
    "LaunchRequest": function () {
        const speechOutput = speechText.welcome;
        const repromptSpeech = "Which content do you want to know ?";

        const cardTitle = "Welcome to CTU !"
        const cardContent = speechOutput;
        var cardImg = {
            smallImageUrl: "https://s3.amazonaws.com/ctuhelper/ctu.jpg",
            largeImageUrl: "https://s3.amazonaws.com/ctuhelper/ctu.jpg"
        }
        this.response.speak(speechOutput)
                    .listen(repromptSpeech)
                    .cardRenderer(cardTitle, cardContent, cardImg);
        this.emit(':responseReady');
    },
    "Introduction": function () {
        const speechOutput = speechText.introduction;
        const cardTitle = "Introduction of CTU !"
        const cardContent = speechOutput;
        var cardImg = {
            smallImageUrl: "https://s3.amazonaws.com/ctuhelper/ctu_gate.JPG",
            largeImageUrl: "https://s3.amazonaws.com/ctuhelper/ctu_gate.JPG"
        }
        this.response.speak(speechOutput)
                    .cardRenderer(cardTitle, cardContent, cardImg);
        this.emit(':responseReady');
    },
    "History": function () {
        const speechOutput = speechText.history;
        const cardTitle = "History of CTU !"
        const cardContent = speechOutput;
        var cardImg = {
            smallImageUrl: "https://s3.amazonaws.com/ctuhelper/ctu_history.png",
            largeImageUrl: "https://s3.amazonaws.com/ctuhelper/ctu_history.png"
        }
        this.response.speak(speechOutput)
                    .cardRenderer(cardTitle, cardContent, cardImg);
        this.emit(':responseReady');
    },
    "FoundYear": function () {
        const speechOutput = speechText.foundYear;
        const cardTitle = "Found Year"
        const cardContent = speechOutput;
        var cardImg = {
            smallImageUrl: "https://s3.amazonaws.com/ctuhelper/ctu_history.png",
            largeImageUrl: "https://s3.amazonaws.com/ctuhelper/ctu_history.png"
        }
        this.response.speak(speechOutput)
                    .cardRenderer(cardTitle, cardContent, cardImg);
        this.emit(':responseReady');
    },
    "CollegeIntent": function () {
        let speechOutput;
        let college =  this.event.request.intent.slots.College.value;
        let cardImg;
        if(college == "engineering technology") {
            speechOutput = speechText.ETInformation;
            cardImg = {
                smallImageUrl: "https://s3.amazonaws.com/ctuhelper/et.jpg",
                largeImageUrl: "https://s3.amazonaws.com/ctuhelper/et.jpg"
            }
        }
        else if(college == "ict" || college == "information and communication technology") {
            speechOutput = speechText.ICTInformation;
            cardImg = {
                smallImageUrl: "https://s3.amazonaws.com/ctuhelper/ict.jpg",
                largeImageUrl: "https://s3.amazonaws.com/ctuhelper/ict.jpg"
            }
        }
        else
            speechOutput = "There is not your college you find";


        const cardTitle = "History of CTU !"
        const cardContent = speechOutput;
        this.response.speak(speechOutput)
                    .cardRenderer(cardTitle, cardContent, cardImg);
        this.emit(':responseReady');
    },
    "ATMPosition": function () {
        if (this.event.request.dialogState == "STARTED" || this.event.request.dialogState == "IN_PROGRESS"){
            this.context.succeed({
                "response": {
                    "directives": [
                        {
                            "type": "Dialog.Delegate"
                        }
                    ],
                    "shouldEndSession": false
                },
                "sessionAttributes": {}
            });
        } else {
            let speechOutput;
            const cardTitle = "ATM Position of CTU !"
            let bank =  this.event.request.intent.slots.Bank.value;

            if(bank == "bidv" || bank == "vietcombank" || bank == "sacombank")
                speechOutput = bank + " ATM is A gate";
            else if(bank == "agribank")
                speechOutput = bank + " ATM is B gate";
            else if(bank == "vietinbank")
                speechOutput = bank + " ATM is C gate";

            const cardContent = speechOutput;

            this.response.speak(speechOutput)
                        .cardRenderer(cardTitle, cardContent);
            this.emit(':responseReady');
        }
    },
    "AMAZON.HelpIntent": function() {
        this.emit("LaunchRequest");
    },
    "AMAZON.NoIntent": function () {
        const speechOutput = "Sorry, i don't understand";
        this.emit(':tell', speechOutput);
    },
    "AMAZON.StopIntent": function () {
        const speechOutput = speechText.goodbye;
        this.emit(":tell", speechOutput, speechOutput);
    },
    "AMAZON.CancelIntent": function () {
        this.emit("AMAZON.StopIntent");
    },
    "Unhandled": function () {
        const speechOutput = "Sorry, i don't know that";
        this.emit(":ask", speechOutput, speechOutput);
    },
    "SessionEndedRequest": function () {
        console.log(`Session ended in help state: ${this.event.request.reason}`);
    },
};

exports.handler = function(event, context, callback) {
    const alexa = Alexa.handler(event, context, callback);
    alexa.appId = APP_ID;
    alexa.registerHandlers(handlers);
    alexa.execute();
};