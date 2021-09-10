const SpotifyHackApi = {
	disableRepeatOne: () => console.log("disableRepeatOne"),
	dislikeCurrent: () => console.log("dislikeCurrent"),
	enableRepeat: () => console.log("enableRepeat"),
	enableRepeatOne: () => console.log("enableRepeatOne"),
	isCurrentLiked: () => console.log("isCurrentLiked"),
	likeCurrent: () => console.log("likeCurrent"),
	next: () => console.log("next"),
	pause: () => console.log("pause"),
	play: () => console.log("play"),
	playPause: () => console.log("playPause"),
	playState: () => console.log("playState"),
	previous: () => console.log("previous"),
	repeatStatus: () => console.log("repeatStatus"),
	toggleLikeCurrent: () => console.log("toggleLikeCurrent"),
	toggleShuffle: () => console.log("toggleShuffle"),

	startListening: () => {
		const ws = new WebSocket("ws://localhost:8080/ws");
		ws.addEventListener("open", (event) => {
			console.info("Hello Server!", event);
			ws.send("Hello Server!");
		});
		ws.addEventListener("close", (event) => {
			console.warn("Bye Server!", event);
		});
		ws.addEventListener("error", (event) => {
			console.error("Error with server", event);
		});
		ws.addEventListener("message", (event) => {
			console.log("Message from server ", event.data);
			switch (event.data) {
				case "disableRepeatOne": {
					SpotifyHackApi.disableRepeatOne();
					break;
				}
				case "dislikeCurrent": {
					SpotifyHackApi.dislikeCurrent();
					break;
				}
				case "enableRepeat": {
					SpotifyHackApi.enableRepeat();
					break;
				}
				case "enableRepeatOne": {
					SpotifyHackApi.enableRepeatOne();
					break;
				}
				case "isCurrentLiked": {
					ws.send(
						"isCurrentLiked:" + SpotifyHackApi.isCurrentLiked(),
					);
					break;
				}
				case "likeCurrent": {
					SpotifyHackApi.likeCurrent();
					break;
				}
				case "next": {
					SpotifyHackApi.next();
					break;
				}
				case "pause": {
					SpotifyHackApi.pause();
					break;
				}
				case "play": {
					SpotifyHackApi.play();
					break;
				}
				case "playPause": {
					SpotifyHackApi.playPause();
					break;
				}
				case "playState": {
					ws.send("playState:" + SpotifyHackApi.playState());
					break;
				}
				case "previous": {
					SpotifyHackApi.previous();
					break;
				}
				case "repeatStatus": {
					ws.send("repeatStatus:" + SpotifyHackApi.repeatStatus());
					break;
				}
				case "toggleLikeCurrent": {
					SpotifyHackApi.toggleLikeCurrent();
					break;
				}
				case "toggleShuffle": {
					SpotifyHackApi.toggleShuffle();
					break;
				}
				default: {
					ws.send("Error:UnknownCommand");
					console.error("Unknown Command: ", event.data);
					break;
				}
			}
		});
	},
};
