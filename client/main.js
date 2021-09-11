const SpotifyHackApi = {
	disableRepeatOne: () => console.log("disableRepeatOne"),
	dislikeCurrent: () => console.log("dislikeCurrent"),
	enableRepeat: () => console.log("enableRepeat"),
	enableRepeatOne: () => console.log("enableRepeatOne"),
	getIsCurrentLiked: () => console.log("isCurrentLiked"),
	likeCurrent: () => console.log("likeCurrent"),
	next: () => console.log("next"),
	pause: () => console.log("pause"),
	play: () => console.log("play"),
	playPause: () => console.log("playPause"),
	getPlayState: () => console.log("playState"),
	previous: () => console.log("previous"),
	getRepeatStatus: () => console.log("repeatStatus"),
	toggleLikeCurrent: () => console.log("toggleLikeCurrent"),
	toggleShuffle: () => console.log("toggleShuffle"),

	startListening: () => {
		let socketOpen = false;
		const ws = new WebSocket("ws://localhost:8080/ws");
		ws.addEventListener("open", (event) => {
			socketOpen = true;
			console.info("Hello Server!", event);
			ws.send(`{"type": "info", "message": "hello server!"}`);
		});
		ws.addEventListener("close", (event) => {
			socketOpen = false;
			console.warn("Bye Server!", event);
		});
		ws.addEventListener("error", (event) => {
			console.error("Error with server", event);
			if (socketOpen)
				ws.send(
					`{"type": "error", "message": "problem with WebSocket client"}`,
				);
			else console.error("Hey the socket is closed");
		});
		ws.addEventListener("message", (event) => {
			console.info("Message from server ", event.data);
			let parsedData;
			try {
				parsedData = JSON.parse(event.data);
			} catch (error) {
				if (socketOpen)
					ws.send(
						`{"type": "error", "message": "failed to parse server's data"}`,
					);
				else console.error("Hey the socket is closed");
				console.error("Failed To parse server's message");
				return;
			}
			if (parsedData.type == "command")
				switch (parsedData.message) {
					case "getIsCurrentLiked": {
						if (socketOpen)
							ws.send(
								`{"type": "getIsCurrentLiked", "message": "${SpotifyHackApi.getIsCurrentLiked()}"}`,
							);
						else console.error("Hey the socket is closed");
						break;
					}
					case "getRepeatStatus": {
						if (socketOpen)
							ws.send(
								`{"type": "getRepeatStatus", "message": "${SpotifyHackApi.getRepeatStatus()}"}`,
							);
						else console.error("Hey the socket is closed");
						break;
					}
					case "getPlayState": {
						if (socketOpen)
							ws.send(
								`{"type": "getPlayState", "message": "${SpotifyHackApi.getPlayState()}"}`,
							);
						else console.error("Hey the socket is closed");
						break;
					}
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
					case "previous": {
						SpotifyHackApi.previous();
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
						if (socketOpen)
							ws.send(
								`{"type": "error", "message": "unknown command"}`,
							);
						else console.error("Hey the socket is closed");
						console.error("Unknown Command: ", event.data);
						break;
					}
				}
		});
	},
};
