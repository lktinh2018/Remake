'use strict';

exports.handler = function(event, context) {
    try {
        //New session
        if(event.session.new) {
            onSessionStarted({requestId: event.request.requestId}, event.session);
        }

        //Events Handler
        if(event.request.type === "LaunchRequest") {
            onLaunch(event.request,
                event.session,
                function callback(sessionAttributes, speechletResponse) {
                    context.succeed(buildResponse(sessionAttributes, speechletResponse));
                });
        } else if(event.request.type === "IntentRequest") {
            onIntent(event.request,
                event.session,                       
                function callback(sessionAttributes, speechletResponse) {
                    context.succeed(buildResponse(sessionAttributes, speechletResponse));
                });
        } else if(event.request.type === "SessionEndedRequest") {
            onSessionEnded(event.request, event.session);
            context.succeed();
        }
    } catch (e) {
        context.fail("Exception: " + e);
    }
};

function getWelcomeResponse(callback) {
    const sessionAttributes = {};
    const cardTitle    = "Welcome to CTU !!!";
    const speechOutput = "Welcome to Can Tho University, I'm CTU helper, I will help you information about Can Tho University like history, colleges, ATM position... Which content do you want to know ?";
    const repromptText = "Which content do you want to know ?";
    const shouldEndSession = false;
    callback(sessionAttributes, buildSpeechletResponse(cardTitle, speechOutput, repromptText, shouldEndSession));
}

function getIntroduction(intent, session, callback) {
    const speechOutput = "Can Tho University , an important state higher education institution in the Mekong Delta, is the cultural, scientific and technical center of the MD and Vietnam. Since its founding in 1966, CTU has been improving and developing itself. Currently, it has nearly 100 undergraduates, 36 Master and 15 Doctoral training programs. Every year CTU receives students on internship programs from the U.S, Belgium, Japan and so on, or under agreements between their universities and CTU.";
    const cardTitle = intent.name;
    let sessionAttributes = {};
    let repromptText = "";
    const shouldEndSession = true;

    callback(sessionAttributes, buildSpeechletResponse(cardTitle, speechOutput, repromptText, shouldEndSession));
}

function getHistory(intent, session, callback) {
    let sessionAttributes = {};
    const cardTitle = intent.name;
    const speechOutput = "On 31 March 1966, Cần Thơ University was established by the government of the Republic of Vietnam. The original university included four faculties: Sciences, Law and Social Sciences, Letters and Pedagogy. After the Fall of Saigon, the university developed into a comprehensive university for the Mekong Delta region with several faculties added. In 2003, the Faculty of Medicine split to form the Can Tho University of Medicine and Pharmacy.";
    let repromptText = "";
    const shouldEndSession = true;
    callback(sessionAttributes, buildSpeechletResponse(cardTitle, speechOutput, repromptText, shouldEndSession));
}

function getFoundYear(intent, session, callback) {
    let sessionAttributes = {};
    const cardTitle = intent.name;
    const speechOutput = "Can Tho University was found in March 3, 1966";
    let repromptText = "";
    const shouldEndSession = true;

    callback(sessionAttributes, buildSpeechletResponse(cardTitle, speechOutput, repromptText, shouldEndSession));
}

function getCollegeInformation(intent, session, callback) {
    let college = intent.slots.College.value;
    if(college === "ict" || college === "information and communication technology")
        getICTInformation(intent, session, callback);
    else if(college === "engineering technology")
        getETInformation(intent, session, callback);

}

function getICTInformation(intent, session, callback) {
    let sessionAttributes = {};
    const cardTitle = intent.name;
    const speechOutput = "The College of Information & Communications Technology (CICT), formerly the Center for Informatics and Electronics (1990), was established in 1994. CICT’s main missions are to offer undergraduate and postgraduate programs, and to participate in scientific research and technology transfer in the field of Information & Communication Technology (ICT).";
    const repromptText = "";
    const shouldEndSession = true;
    callback(sessionAttributes, buildSpeechletResponse(cardTitle, speechOutput, repromptText, shouldEndSession));

}

function getETInformation(intent, session, callback) {
    let sessionAttributes = {};
    const cardTitle = intent.name;
    const speechOutput = "As one of the major unit of University of Can Tho, College of Engineering Technology is responsible for training, conducting research and transferring technology in engineering for the Mekong Delta region and the country";
    const repromptText = "";
    const shouldEndSession = true;
    callback(sessionAttributes, buildSpeechletResponse(cardTitle, speechOutput, repromptText, shouldEndSession));
}

function getATMPosition(intent, session, callback) {
    let sessionAttributes = {};
    const cardTitle = "ATM Position";
    const repromptText = "";
    const shouldEndSession = true;
    var bank = intent.slots.Bank.value;
    var speechOutput;
    if(bank === "vietcombank" || bank === "sacombank" || bank === "BIDV")
        speechOutput = bank + " ATM is A gate";
    else if(bank === "agribank")
        speechOutput = bank + " ATM is B gate";
    else if(bank === "vietinbank")
        speechOutput = bank + " ATM is C gate";
    else 
        speechOutput = "Your bank is doesn't have atm in CTU";
    callback(sessionAttributes, buildSpeechletResponse(cardTitle, speechOutput, repromptText, shouldEndSession));
}

function getGoodbye(callback) {
    let sessionAttributes = {};
    const cardTitle = "Good bye !!!";
    const speechOutput = "Good bye, see you again !!!";
    const repromptText = "";
    const shouldEndSession = true;
    callback(sessionAttributes, buildSpeechletResponse(cardTitle, speechOutput, repromptText, shouldEndSession));
}
//Events
function onSessionStarted(sessionStartedRequest, session) {
    console.log("onSessionStarted requestId=" + sessionStartedRequest.requestId
        + ", sessionId=" + session.sessionId);
}

function onLaunch(launchRequest, session, callback) {
    getWelcomeResponse(callback);
}

function onIntent(intentRequest, session, callback) {
    var intent     = intentRequest.intent;
    var intentName = intentRequest.intent.name;
    if(intentName === "Introduction" || intentName === "AMAZONE.HelpIntent") {
        getIntroduction(intent, session, callback);
    } else if(intentName === "FoundYear") {
        getFoundYear(intent, session, callback);
    } else if(intentName === "History") {
        getHistory(intent, session, callback);
    } else if(intentName === "CollegeIntent") {
        getCollegeInformation(intent, session, callback);
    } else if(intentName === "ATMPosition") {
        getATMPosition(intent, session, callback);
    } else if (intentName === 'AMAZON.StopIntent' || intentName === 'AMAZON.CancelIntent') {
        getGoodbye(callback);
    } else {
        throw "Invalid intent";
    }
}

function onSessionEnded(sessionEndedRequest, session) {
    console.log("onSessionEnded requestId=" + sessionEndedRequest.requestId + ", sessionId=" + session.sessionId);
}

/*------Helper functions to build responses------*/ 

function buildSpeechletResponse(title, output, repromptText, shouldEndSession) {
    return {
        outputSpeech: {
            type: "PlainText",
            text: output
        },
        card: {
            type: "Simple",
            title: title,
            content: output
        },
        reprompt: {
            outputSpeech: {
                type: "PlainText",
                text: repromptText
            }
        },
        shouldEndSession,
    };
}

function buildSpeechletResponseWithoutCard(output, repromptText, shouldEndSession) {
    return {
        outputSpeech: {
            type: "PlainText",
            text: output
        },
        repromt: {
            outputSpeech: {
                type: "PlainText",
                text: repromptText
            }
        },
        shouldEndSession: shouldEndSession
    };
}

function buildResponse(sessionAttributes, speechletResponse) {
    return {
        version: "1.0",
        sessionAttributes: sessionAttributes,
        response: speechletResponse
    };
}