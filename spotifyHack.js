const SpotifyHackApi = {
	next: () =>
		document.querySelector(".main-skipForwardButton-button").click(),
	previous: () =>
		document.querySelector(".main-skipBackButton-button").click(),
	toggleShuffle: () =>
		document.querySelector(".main-shuffleButton-button").click(),
	playPause: () =>
		document
			.querySelector(
				"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > button",
			)
			.click(),

	playState: () => {
		return document.querySelector(
			"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > button",
		).title;
	},

	play: () => {
		if (SpotifyHackApi.playState() == "Play")
			document
				.querySelector(
					"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > button",
				)
				.click();
	},

	pause: () => {
		if (SpotifyHackApi.playState() == "Pause")
			document
				.querySelector(
					"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > div.player-controls__buttons > button",
				)
				.click();
	},

	repeatStatus: () => {
		return document.querySelector(".main-repeatButton-button").title;
	},

	enableRepeat: () => {
		if (SpotifyHackApi.repeatStatus() == "Enable repeat")
			document.querySelector(".main-repeatButton-button").click();
		else if (SpotifyHackApi.repeatStatus() == "Disable repeat") {
			document.querySelector(".main-repeatButton-button").click();
			document.querySelector(".main-repeatButton-button").click();
		}
	},
	enableRepeatOne: () => {
		if (SpotifyHackApi.repeatStatus() == "Enable repeat one")
			document.querySelector(".main-repeatButton-button").click();
		else if (SpotifyHackApi.repeatStatus() == "Enable repeat") {
			document.querySelector(".main-repeatButton-button").click();
			document.querySelector(".main-repeatButton-button").click();
		}
	},
	disableRepeatOne: () => {
		if (SpotifyHackApi.repeatStatus() == "Disable repeat")
			document.querySelector(".main-repeatButton-button").click();
		else if (SpotifyHackApi.repeatStatus() == "Enable repeat one") {
			document.querySelector(".main-repeatButton-button").click();
			document.querySelector(".main-repeatButton-button").click();
		}
	},

	isCurrentLiked: () => {
		switch (
			document.querySelector(
				"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > button",
			).title
		) {
			case "Remove from Your Library": {
				return true;
			}
			case "Save to Your Library": {
				return false;
			}
			default: {
				console.error("Oh on");
				return false;
			}
		}
	},

	toggleLikeCurrent: () => {
		document
			.querySelector(
				"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > button",
			)
			.click();
	},
	likeCurrent: () => {
		if (!SpotifyHackApi.isCurrentLiked())
			document
				.querySelector(
					"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > button",
				)
				.click();
	},
	dislikeCurrent: () => {
		if (SpotifyHackApi.isCurrentLiked())
			document
				.querySelector(
					"#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div > div > button",
				)
				.click();
	},

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
