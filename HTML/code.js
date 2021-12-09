
const firebaseConfig = {
  apiKey: "AIzaSyB4AwTcKfWHimXPzdJwo_z53GsJgtGSpbQ",
  authDomain: "iot2farebasev.firebaseapp.com",
  databaseURL: "https://iot2farebasev-default-rtdb.firebaseio.com",
  projectId: "iot2farebasev",
  storageBucket: "iot2farebasev.appspot.com",
  messagingSenderId: "105611546553",
  appId: "1:105611546553:web:012b5ae3e90d9989f97068",
  measurementId: "${config.measurementId}"
};

firebase.initializeApp(firebaseConfig);

var db = firebase.database();
var reviews = document.getElementById("reviews");
var reviewsRef = db.ref("/reviews");

reviewsRef.on("child_added", data => {
    console.log(data.val());
})
