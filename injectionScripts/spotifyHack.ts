/// <reference path="./globals.d.ts" />

const Hackify = {
	_click: (selector: string): void =>
		document.querySelector<HTMLElement>(selector).click(),
	_getArialLabel: (selector: string): string =>
		document.querySelector<HTMLElement>(selector).ariaLabel,
	_getInnerText: (selector: string): string =>
		document.querySelector<HTMLElement>(selector).innerText,
	_getElement: (selector: string): HTMLElement =>
		document.querySelector<HTMLElement>(selector),

	_likeBtn: ".main-addButton-button",
	_currentSong: "#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div.main-nowPlayingBar-left > div > div.main-trackInfo-container.ellipsis-one-line > div.main-trackInfo-name.ellipsis-one-line.main-type-mesto > span > a",
	_currentSongArtist: "#main > div > div.Root__top-container > div.Root__now-playing-bar > footer > div > div.main-nowPlayingBar-left > div > div.main-trackInfo-container.ellipsis-one-line > div.main-trackInfo-artists.ellipsis-one-line.main-type-finale > span > span > a",

	getInfo: () => ({
		currentSong: Hackify.getCurrentSong(),
		currentSongArtist: Hackify.getCurrentSongArtist(),
		currentSongAlbumArt: Hackify.getCurrentSongAlbumArt(),
		isCurrentLiked: Hackify.getIsCurrentLiked(),
		repeatStatus: Hackify.getRepeatStatus(),
		shuffleStatus: Hackify.getIsShuffleOn(),
	}),

	getCurrentSongArtist: () => Hackify._getInnerText(Hackify._currentSongArtist),
	getCurrentSong: () => Hackify._getInnerText(Hackify._currentSong),
	getCurrentSongAlbumArt: () => "Unavalible in this client",

	getIsShuffleOn: () => Spicetify.Player.getShuffle(),
	toggleShuffle: () => Spicetify.Player.toggleShuffle(),
	shuffleOn: () => Spicetify.Player.setShuffle(true),
	shuffleOff: () => Spicetify.Player.setShuffle(false),

	getIsPlaying: () => Spicetify.Player.isPlaying(),
	playPause: () => Spicetify.Player.togglePlay(),
	play: () => Spicetify.Player.play(),
	pause: () => Spicetify.Player.pause(),
	next: () => Spicetify.Player.next(),
	previous: () => Spicetify.Player.back(),

	getRepeatStatus: () => Spicetify.Player.getRepeat(),
	disableRepeat: () => Spicetify.Player.setRepeat(0),
	enableRepeatOne: () => Spicetify.Player.setRepeat(1),
	enableRepeat: () => Spicetify.Player.setRepeat(2),

	getIsCurrentLiked: () =>
		Hackify._getElement(Hackify._likeBtn).ariaChecked === "true",
	toggleLike: () => Hackify._click(Hackify._likeBtn),
	likeCurrent: () => Hackify.getIsCurrentLiked() || Hackify.toggleLike(),
	dislikeCurrent: () => Hackify.getIsCurrentLiked() && Hackify.toggleLike(),

	ws: null,
	interval: null,
	startListeningCalls: 0,

	wsTrySend: (type: string, message: any) => {
		if (Hackify.ws != null)
			if (Hackify.ws.readyState == WebSocket.OPEN)
				Hackify.ws.send(JSON.stringify({ type, message }));
			else console.error("Hey the socket is closed");
		else console.error("Hey the socket is not defined");
	},

	startListening: () => {
		console.info("Start Listening Call: ", ++Hackify.startListeningCalls);
		let socketOpen = false;

		if (Hackify.ws != null) {
			if (Hackify.ws.readyState === WebSocket.OPEN) return true;
			else {
				delete Hackify.ws;
				Hackify.ws = null;
			}
		}

		try {
			Hackify.ws = new WebSocket("ws://localhost:8080/ws");
		} catch (e) {
			return false;
		}

		if (Hackify.ws != null)
			if (Hackify.ws.readyState === WebSocket.OPEN)
				clearInterval(Hackify.interval);

		Hackify.ws.addEventListener("open", (event: Event) => {
			if (Hackify.interval != null) {
				clearInterval(Hackify.interval);
				Hackify.interval = null;
			}
			socketOpen = true;
			console.info("Hello Server!", event);
			Hackify.ws.send(`{"type": "info", "message": "hello server!"}`);
		});

		Hackify.ws.addEventListener("close", (event: CloseEvent) => {
			socketOpen = false;
			console.warn("Bye Server!", event);
			if (Hackify.interval === null)
				Hackify.interval = setInterval(() => {
					Hackify.startListening();
					if (Hackify.ws != null)
						if (Hackify.ws.readyState === WebSocket.OPEN)
							clearInterval(Hackify.interval);
				}, 2500);
		});

		Hackify.ws.addEventListener("error", (event: ErrorEvent) => {
			console.error("Error with server", event);
			if (socketOpen)
				Hackify.ws.send(
					`{"type": "error", "message": "problem with WebSocket client"}`,
				);
			else console.error("Hey the socket is closed");
		});

		Hackify.ws.addEventListener("message", (event: MessageEvent) => {
			console.info("Message from server ", event.data);
			let parsedData: { type: string; message: string };
			try {
				parsedData = JSON.parse(event.data);
				if (!parsedData.type)
					throw SyntaxError(
						`No or blank tyoe in format '{"type": "info|error|command|code", "message": ""}'`,
					);
				if (!parsedData.message)
					throw SyntaxError(
						`No or blank message in format '{"type": "info|error|command|code", "message": ""}'`,
					);
			} catch (err: SyntaxError | any) {
				Hackify.ws.send(
					`{"type": "error", "message": "${err.toString()}"}`,
				);
				console.error(`Error Parsing '${err.toString()}'`);
				return;
			}
			if (parsedData.type === "code") {
				Hackify.wsTrySend("code", eval(parsedData.message));
			} else if (parsedData.type === "command") {
				// prettier-ignore
				switch (parsedData.message) {

					case "play":                 Hackify.play()                                                      ; break ;
					case "pause":                Hackify.pause()                                                     ; break ;
					case "playPause":            Hackify.playPause()                                                 ; break ;
					case "next":                 Hackify.next()                                                      ; break ;
					case "previous":             Hackify.previous()                                                  ; break ;

					case "toggleLike":           Hackify.toggleLike()                                                ; break ;
					case "likeCurrent":          Hackify.likeCurrent()                                               ; break ;
					case "dislikeCurrent":       Hackify.dislikeCurrent()                                            ; break ;

					case "enableRepeat":         Hackify.enableRepeat()                                              ; break ;
					case "enableRepeatOne":      Hackify.enableRepeatOne()                                           ; break ;
					case "disableRepeat":        Hackify.disableRepeat()                                             ; break ;

					case "toggleShuffle":        Hackify.toggleShuffle()                                             ; break ;

					case "getInfo":              Hackify.wsTrySend("getInfo",              JSON.stringify(Hackify.getInfo()))              ; break ;
					case "getCurrentSong":       Hackify.wsTrySend("getCurrentSong",       Hackify.getCurrentSong())       ; break ;
					case "getCurrentSongArtist": Hackify.wsTrySend("getCurrentSongArtist", Hackify.getCurrentSongArtist()) ; break ;
					case "getCurrentSongAlbumArt": Hackify.wsTrySend("getCurrentSongAlbumArt", Hackify.getCurrentSongAlbumArt()) ; break ;
					case "getIsCurrentLiked":    Hackify.wsTrySend("getIsCurrentLiked",    Hackify.getIsCurrentLiked())    ; break ;
					case "getIsPlaying":         Hackify.wsTrySend("getIsPlaying",         Hackify.getIsPlaying())         ; break ;
					case "getRepeatStatus":      Hackify.wsTrySend("getRepeatStatus",      Hackify.getRepeatStatus())      ; break ;

					default: {
						Hackify.wsTrySend("error", `unknown command${parsedData.message}`);
						console.error("Unknown Command: ", event.data); 
						break;
					}

				}
			}
		});

		return Hackify.ws.readyState === WebSocket.OPEN;
	},

	render: () => {
		const activeBtn =
			'<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" aria-hidden="true" role="img" width="1.33em" height="1em" preserveAspectRatio="xMidYMid meet" viewBox="0 0 256 193"><path d="M192.44 144.645h31.78V68.339l-35.805-35.804l-22.472 22.472l26.497 26.497v63.14zm31.864 15.931H113.452L86.954 134.08l11.237-11.236l21.885 21.885h45.028l-44.357-44.441l11.32-11.32l44.357 44.358V88.296l-21.801-21.801l11.152-11.153L110.685 0H0l31.696 31.696v.084H97.436l23.227 23.227l-33.96 33.96L63.476 65.74V47.712h-31.78v31.193l55.007 55.007L64.314 156.3l35.805 35.805H256l-31.696-31.529z" fill="#ffffff""/></svg>';
		const inactiveBtn =
			'<svg xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" aria-hidden="true" role="img" width="1.33em" height="1em" preserveAspectRatio="xMidYMid meet" viewBox="0 0 256 193"><path d="M192.44 144.645h31.78V68.339l-35.805-35.804l-22.472 22.472l26.497 26.497v63.14zm31.864 15.931H113.452L86.954 134.08l11.237-11.236l21.885 21.885h45.028l-44.357-44.441l11.32-11.32l44.357 44.358V88.296l-21.801-21.801l11.152-11.153L110.685 0H0l31.696 31.696v.084H97.436l23.227 23.227l-33.96 33.96L63.476 65.74V47.712h-31.78v31.193l55.007 55.007L64.314 156.3l35.805 35.805H256l-31.696-31.529z" fill="#231F20"/></svg>';

		const SpotifyHackBtn = new Spicetify.Topbar.Button(
			"Start Listening",
			inactiveBtn,
			() => {
				Hackify.startListening();
				if (Hackify.ws != null)
					if (Hackify.ws.readyState === WebSocket.OPEN) {
						SpotifyHackBtn.icon = activeBtn;
					}
			},
		);

		setInterval(() => {
			if (Hackify.ws != null) {
				if (Hackify.ws.readyState == WebSocket.OPEN) {
					SpotifyHackBtn.icon = activeBtn;
				} else {
					SpotifyHackBtn.icon = inactiveBtn;
				}
			}
		}, 1000);
	},
};

(() => {
	Hackify.render();
})();
