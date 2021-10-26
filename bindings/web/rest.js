$ = document.querySelector.bind(document);

const BASE_URL = "http://localhost:8080/command/";

$("#nextRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "next").then(d => console.log(d));
});
$("#playRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "play").then(d => console.log(d));
});
$("#pauseRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "pause").then(d => console.log(d));
});
$("#previousRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "previous").then(d => console.log(d));
});
$("#playPauseRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "playPause").then(d => console.log(d));
});
$("#likeCurrentRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "likeCurrent").then(d => console.log(d));
});
$("#enableRepeatRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "enableRepeat").then(d => console.log(d));
});
$("#repeatStatusRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "repeatStatus").then(d => console.log(d));
});
$("#toggleShuffleRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "toggleShuffle").then(d => console.log(d));
});
$("#dislikeCurrentRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "dislikeCurrent").then(d => console.log(d));
});
$("#isCurrentLikedRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "isCurrentLiked").then(d => console.log(d));
});
$("#enableRepeatOneRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "enableRepeatOne").then(d => console.log(d));
});
$("#disableRepeatOneRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "disableRepeatOne").then(d => console.log(d));
});
$("#toggleLikeCurrentRestBtn").addEventListener("click", () => {
	fetch(BASE_URL + "toggleLikeCurrent").then(d => console.log(d));
});
