Vue.component('wallet-summary', {
	data() {
		return {
			data: null,
			loading: false
		}
	},
	methods: {
		update() {
			this.loading = true;
			fetch('/wapi/wallet/accounts')
				.then(response => response.json())
				.then(data => {
					this.loading = false;
					this.data = data;
				})
		}
	},
	created() {
		this.update();
	},
	template: `
		<div>
			<v-progress-linear :active="loading" indeterminate absolute top></v-progress-linear>

			<div v-for="item in data" :key="item.address">
				<account-summary :index="item.account" :account="item"></account-summary>
			</div>

			<v-btn to="/wallet/create" outlined color="primary" class="my-2">{{ $t('wallet_summary.new_wallet') }}</v-btn>
		</div>
		`
})

Vue.component('account-menu', {
	props: {
		index: Number
	},
	template: `
		<v-btn-toggle class="d-flex flex-wrap">
			<v-btn :to="'/wallet/account/' + index" exact>{{ $t('account_menu.balance') }}</v-btn>
			<v-btn :to="'/wallet/account/' + index + '/nfts'" v-if=false>{{ $t('account_menu.nfts') }}</v-btn>
			<v-btn :to="'/wallet/account/' + index + '/contracts'">{{ $t('account_menu.contracts') }}</v-btn>
			<v-btn :to="'/wallet/account/' + index + '/send'">{{ $t('account_menu.send') }}</v-btn>
			<v-btn :to="'/wallet/account/' + index + '/history'">{{ $t('account_menu.history') }}</v-btn>
			<v-btn :to="'/wallet/account/' + index + '/log'">{{ $t('account_menu.log') }}</v-btn>
			<v-btn :to="'/wallet/account/' + index + '/offer'">{{ $t('account_menu.offer') }}</v-btn>
			<v-btn :to="'/wallet/account/' + index + '/liquid'">{{ $t('account_menu.liquidity') }}</v-btn>
			<v-btn :to="'/wallet/account/' + index + '/plotnfts'">PlotNFTs</v-btn>
			<v-btn :to="'/wallet/account/' + index + '/details'">{{ $t('account_menu.info') }}</v-btn>
			<v-btn :to="'/wallet/account/' + index + '/options'"><v-icon>mdi-cog</v-icon></v-btn>
		</v-btn-toggle>
		`
})

Vue.component('account-header', {
	props: {
		index: Number,
		account: Object
	},
	data() {
		return {
			info: {
				name: null,
				index: null,
				address: null,
				with_passphrase: null
			},
			is_locked: null,
			passphrase_dialog: false
		}
	},
	computed: {
		address() {
			return this.info.address ? this.info.address : "N/A";
		}
	},
	methods: {
		update() {
			if(this.account) {
				this.info = this.account;
			} else {
				fetch('/wapi/wallet/account?index=' + this.index)
					.then(response => response.json())
					.then(data => this.info = data);
			}
			this.update_lock();
		},
		update_lock() {
			fetch('/api/wallet/is_locked?index=' + this.index)
				.then(response => response.json())
				.then(data => this.is_locked = data);
		},
		toggle_lock() {
			if(this.is_locked) {
				this.passphrase_dialog = true;
			} else {
				const req = {};
				req.index = this.index;
				fetch('/api/wallet/lock', {body: JSON.stringify(req), method: "post"})
					.then(() => this.update_lock());
			}
		},
		unlock(passphrase) {
			const req = {};
			req.index = this.index;
			req.passphrase = passphrase;
			fetch('/api/wallet/unlock', {body: JSON.stringify(req), method: "post"})
				.then(response => {
					if(response.ok) {
						this.update();
					} else {
						response.text().then(data => {
							alert(data);
						});
					}
				});
		},
		copyToClipboard(address) {
			navigator.clipboard.writeText(address);
		}
	},
	created() {
		this.update();
		this.timer = setInterval(() => { this.update_lock(); }, 10000);
	},
	beforeDestroy() {
		clearInterval(this.timer);
	},
	template: `
		<div>
			<v-chip label>{{ $t('account_header.wallet') }} #{{index}}</v-chip>
			<template v-if="info.address">
				<v-chip label :class="{'pr-0': navigator.clipboard}">
					{{ address }}
					<template v-if="navigator.clipboard">
						<v-btn @click="copyToClipboard(address)" text icon>
							<v-icon small class="pr-0">mdi-content-copy</v-icon>
						</btn>
					</template>
				</v-chip>
			</template>
			<v-chip v-if="info.name" label>{{info.name}}</v-chip>
			<v-btn v-if="info.with_passphrase && (is_locked != null)" @click="toggle_lock()" text icon>
				<v-icon small class="pr-0">{{ is_locked ? "mdi-lock" : "mdi-lock-open-variant" }}</v-icon>
			</btn>
			<passphrase-dialog v-model="passphrase_dialog" @submit="p => unlock(p)"/>
		</div>
		`
})

Vue.component('account-summary', {
	props: {
		index: Number,
		account: Object
	},
	template: `
		<v-card class="my-2">
			<v-card-text>
				<account-header :index="index" :account="account"></account-header>
				<account-menu :index="index" class="my-2"></account-menu>				
				<account-balance :index="index"></account-balance>
			</v-card-text>
		</v-card>
		`
})

Vue.component('account-balance', {
	props: {
		index: Number,
	},
	data() {
		return {
			data: [],
			loaded: false,
			timer: null
		}
	},
	computed: {
		headers() {
			return [
				{ text: this.$t('account_balance.balance'), value: 'total' },
				{ text: this.$t('account_balance.reserved'), value: 'reserved' },
				{ text: this.$t('account_balance.spendable'), value: 'spendable' },
				{ text: this.$t('account_balance.token'), value: 'token' },
				{ text: this.$t('account_balance.contract'), value: 'contract', width: '50%' },
			]
		}
	},
	methods: {
		update() {
			fetch('/wapi/wallet/balance?index=' + this.index)
				.then(response => response.json())
				.then(data => {
					this.loaded = true;
					this.data = data.balances;
				});
		}
	},
	created() {
		this.update();
		this.timer = setInterval(() => { this.update(); }, 10000);
	},
	beforeDestroy() {
		clearInterval(this.timer);
	},
	template: `
		<v-data-table
			:headers="headers"
			:items="data"
			:loading="!loaded"
			hide-default-footer
			disable-sort
			disable-pagination
			class="elevation-2"
		>

			<template v-slot:progress>
				<v-progress-linear indeterminate absolute top></v-progress-linear>
				<v-skeleton-loader type="table-row-divider@3" v-if="data.length == 0"/>
			</template>

			<template v-slot:item.contract="{ item }">
				<router-link :to="'/explore/address/' + item.contract">{{item.is_native ? '' : item.contract}}</router-link>
			</template>

			<template v-slot:item.total="{ item }">
				<b>{{amount_format(item.total)}}</b>
			</template>
			<template v-slot:item.reserved="{ item }">
				<b>{{amount_format(item.reserved)}}</b>
			</template>
			<template v-slot:item.spendable="{ item }">
				<b>{{amount_format(item.spendable)}}</b>
			</template>

			<template v-slot:item.token="{ item }">
				<div :class="{'text--disabled': !item.is_validated}">{{item.symbol}}</div>
			</template>

		</v-data-table>
		`
})

Vue.component('balance-table', {
	props: {
		address: String,
		show_empty: Boolean
	},
	data() {
		return {
			data: [],
			loading: false,
			loaded: false,
			timer: null
		}
	},
	computed: {
		headers() {
			return [
				{ text: this.$t('balance_table.balance'), value: 'total'},
				{ text: this.$t('balance_table.locked'), value: 'locked'},
				{ text: this.$t('balance_table.spendable'), value: 'spendable'},
				{ text: this.$t('balance_table.token'), value: 'symbol'},
				{ text: this.$t('balance_table.contract'), value: 'contract', width: '50%'},
			]
		}
	},
	methods: {
		update() {
			this.loading = true;
			fetch('/wapi/balance?id=' + this.address)
				.then(response => response.json())
				.then(data => {
					this.loading = false;
					this.loaded = true;
					this.data = data.balances;
				});
		}
	},
	watch: {
		address() {
			this.update();
		}
	},
	created() {
		this.update();
		this.timer = setInterval(() => { this.update(); }, 10000);
	},
	beforeDestroy() {
		clearInterval(this.timer);
	},
	template: `
		<div>
		<v-data-table
			:headers="headers"
			:items="data"
			:loading="!loaded"
			hide-default-footer
			disable-sort
			disable-pagination
			class="elevation-2"
			v-if="!loaded || loaded && (data.length || show_empty)"
		>
			<template v-slot:item.total="{ item }">
				<b>{{amount_format(item.total)}}</b>
			</template>
			<template v-slot:item.locked="{ item }">
				<b>{{amount_format(item.locked)}}</b>
			</template>
			<template v-slot:item.spendable="{ item }">
				<b>{{amount_format(item.spendable)}}</b>
			</template>

			<template v-slot:item.contract="{ item }">
				<router-link :to="'/explore/address/' + item.contract">{{item.is_native ? '' : item.contract}}</router-link>
			</template>
		</v-data-table>

		<template v-if="!data && loading">
			<div class="ui basic loading placeholder segment"></div>
		</template>
		</div>
		`
})

Vue.component('nft-table', {
	props: {
		index: Number
	},
	data() {
		return {
			nfts: []
		}
	},
	computed: {
		headers() {
			return [
				{ text: 'NFT', value: 'item' },
			]
		}
	},
	methods: {
		update() {
			fetch('/wapi/wallet/balance?index=' + this.index)
				.then(response => response.json())
				.then(data => this.nfts = data.nfts);
		}
	},
	created() {
		this.update()
	},
	template: `
		<v-data-table
			:headers="headers"
			:items="nfts"
			hide-default-footer
			disable-sort
			disable-pagination
			class="elevation-2"
		>
			<template v-slot:item.item="{ item }">
				<router-link :to="'/explore/address/' + item">{{item}}</router-link>
			</template>
		</v-data-table>
		`
})

Vue.component('account-history', {
	props: {
		index: Number,
		limit: Number,
		memo: {
			default: null,
			type: String
		},
		type: {
			default: null,
			type: String
		},
		currency: {
			default: null,
			type: String
		}
	},
	data() {
		return {
			data: [],
			loading: true,
			timer: null 
		}
	},
	computed: {
		headers() {
			return [
				{ text: this.$t('account_history.height'), value: 'height' },
				{ text: this.$t('account_history.type'), value: 'type' },
				{ text: this.$t('account_history.amount'), value: 'value' },
				{ text: this.$t('account_history.token'), value: 'token' },
				{ text: this.$t('account_history.address'), value: 'address' },
				{ text: "Memo", value: 'memo' },
				{ text: this.$t('account_history.link'), value: 'link' },
				{ text: this.$t('account_history.time'), value: 'time' },
			]
		}
	},
	methods: {
		update(reload) {
			if(reload) {
				this.data = [];
				this.loading = true;
			}
			fetch('/wapi/wallet/history?limit=' + this.limit + '&index=' + this.index + '&type=' + this.type + '&memo=' + this.memo + '&currency=' + this.currency)
				.then(response => response.json())
				.then(data => {
					this.loading = false;
					this.data = data;
				});
		}
	},
	watch: {
		type() {
			this.update(true);
		},
		currency() {
			this.update(true);
		},
		memo() {
			this.update(false);
		}
	},
	created() {
		this.update();
		this.timer = setInterval(() => { this.update(); }, 60000);
	},
	beforeDestroy() {
		clearInterval(this.timer);
	},
	template: `
		<v-data-table
			:headers="headers"
			:items="data"
			:loading="loading"
			hide-default-footer
			disable-sort
			disable-pagination
			class="elevation-2"
		>
			<template v-slot:progress>
				<v-progress-linear indeterminate absolute top></v-progress-linear>
				<v-skeleton-loader type="table-row-divider@6" />
			</template>

			<template v-slot:item.height="{ item }">
				<template v-if="item.is_pending">
					<i>pending</i>
				</template>
				<template v-else>
					<router-link :to="'/explore/block/height/' + item.height">{{item.height}}</router-link>
				</template>
			</template>	
			
			<template v-slot:item.type="{ item }">
				<span :class="get_tx_type_color(item.type, $vuetify.theme.dark)">{{item.type}}</span>
			</template>

			<template v-slot:item.value="{ item }">
				<b>{{item.value}}</b>
			</template>

			<template v-slot:item.token="{ item }">
				<template v-if="item.is_native">
					{{item.symbol}}
				</template>
				<template v-else>
					<router-link :to="'/explore/address/' + item.contract">{{item.is_nft ? "[NFT]" : item.symbol}}{{item.is_validated ? "" : "?"}}</router-link>
				</template>
			</template>

			<template v-slot:item.memo="{ item }">
				<span style="word-break: break-all;">{{ item.memo }}</span>
			</template>

			<template v-slot:item.address="{ item }">
				<router-link :to="'/explore/address/' + item.address">{{get_short_addr(item.address)}}</router-link>
			</template>
			
			<template v-slot:item.link="{ item }">
				<tx-type-link :type="item.type" :id="item.txid"/>
			</template>

			<template v-slot:item.time="{ item }">
				<template v-if="!item.is_pending">
					<span class="text-no-wrap">{{new Date(item.time * 1000).toLocaleString()}}</span>
				</template>
			</template>

		</v-data-table>
		`
})

Vue.component('account-history-form', {
	props: {
		index: Number,
		limit: Number
	},
	data() {
		return {
			type: null,
			currency: null,
			memo: null,
			tokens: []
		}
	},
	methods: {
		update() {
			fetch('/wapi/wallet/tokens')
				.then(response => response.json())
				.then(data => this.tokens = data);
		}
	},
	computed: {
		select_types() {
			return [
				{text: this.$t('account_history_form.any'), value: null},
				{text: this.$t('account_history_form.spend'), value: "SPEND"},
				{text: this.$t('account_history_form.receive'), value: "RECEIVE"},
				{text: this.$t('account_history_form.reward'), value: "REWARD"},
				{text: "VDF " + this.$t('account_history_form.reward'), value: "VDF_REWARD"},
				{text: this.$t('account_history_form.tx_fee'), value: "TXFEE"}
			];
		},
		select_tokens() {
			const res = [{text: this.$t('account_history_form.any'), value: null}];
			for(const token of this.tokens) {
				let text = token.symbol;
				if(!token.is_native) {
					text += " - [" + token.currency + "]";
				}
				res.push({text: text, value: token.currency});
			}
			return res;
		}
	},
	created() {
		this.update();
	},
	template: `
		<div>
			<v-card class="my-2">
				<v-card-text>
					<v-row>
						<v-col cols="3">
							<v-select v-model="type" :label="$t('account_history.type')"
								:items="select_types" item-text="text" item-value="value" :disabled="memo != null && memo.length > 0">
							</v-select>
						</v-col>
						<v-col>
							<v-select v-model="currency" :label="$t('account_history.token')"
								:items="select_tokens" item-text="text" item-value="value">
							</v-select>
						</v-col>
					</v-row>
					<v-text-field type="text" label="Memo" v-model="memo"/>
				</v-card-text>
			</v-card>
			<account-history :index="index" :limit="limit" :type="type" :memo="memo" :currency="currency"></account-history>
		</div>
	`
})

Vue.component('account-tx-history', {
	props: {
		index: Number,
		limit: Number
	},
	data() {
		return {
			data: [],
			loading: true,
			timer: null			
		}
	},
	computed: {
		headers() {
			return [
				{ text: this.$t('account_tx_history.height'), value: 'height' },
				{ text: "Type", value: 'note' },
				{ text: "Fee", value: 'fee' },
				{ text: this.$t('account_tx_history.confirmed'), value: 'confirmed' },
				{ text: this.$t('account_tx_history.status'), value: 'state' },
				{ text: this.$t('account_tx_history.transaction_id'), value: 'transaction_id' },
				{ text: this.$t('account_tx_history.time'), value: 'time' },
			]
		}
	},
	methods: {
		update() {
			fetch('/wapi/wallet/tx_history?limit=' + this.limit + '&index=' + this.index)
				.then(response => response.json())
				.then(data => {
					this.loading = false;
					this.data = data;
				});
		}
	},
	created() {
		this.update();
		this.timer = setInterval(() => { this.update(); }, 10000);
	},
	beforeDestroy() {
		clearInterval(this.timer);
	},
	template: `
		<v-data-table
			:headers="headers"
			:items="data"
			:loading="loading"
			hide-default-footer
			disable-sort
			disable-pagination
			class="elevation-2"
		>

			<template v-slot:progress>
				<v-progress-linear indeterminate absolute top></v-progress-linear>
				<v-skeleton-loader type="table-row-divider@6" />
			</template>

			<template v-slot:item.height="{ item }">
				<template v-if="item.height">
					<router-link :to="'/explore/block/height/' + item.height">{{item.height}}</router-link>
				</template>
			</template>
			
			<template v-slot:item.fee="{ item }">
				<template v-if="item.height && item.fee">
					<b>{{(item.fee.value).toFixed(3)}}</b> MMX
				</template>
			</template>
			
			<template v-slot:item.state="{ item }">
				<div :class="{'red--text': item.state == 'failed'}">{{ $t(item.state) }}</div>
			</template>

			<template v-slot:item.transaction_id="{ item }">
				<router-link :to="'/explore/transaction/' + item.id">{{get_short_hash(item.id, 16)}}</router-link>
			</template>

			<template v-slot:item.confirmed="{ item }">
				{{item.confirm ? item.confirm > 1000 ? "> 1000" : item.confirm : null}}
			</template>

			<template v-slot:item.time="{ item }">
				{{new Date(item.time).toLocaleString()}}
			</template>

		</v-data-table>
		`
})

Vue.component('account-contract-summary', {
	props: {
		index: Number,
		address: String,
		contract: Object
	},
	methods: {
		deposit() {
			this.$router.push("/wallet/account/" + this.index + "/send/" + this.address);
		},
		withdraw() {
			this.$router.push("/wallet/account/" + this.index + "/send_from/" + this.address);
		}
	},
	template: `
		<v-card class="my-2">
			<v-card-text>
				<v-chip label>{{contract.__type}}</v-chip>
				<v-chip label>{{address}}</v-chip>
				<object-table :data="contract" class="my-2"></object-table>
				<balance-table :address="address"></balance-table>
				<div v-if="contract.__type != 'mmx.contract.Executable'" class="mt-4">
					<v-btn outlined @click="deposit">{{ $t('account_contract_summary.deposit') }}</v-btn>
					<v-btn outlined @click="withdraw">{{ $t('account_contract_summary.withdraw') }}</v-btn>
				</div>
			</v-card-text>
		</v-card>
		`
})

Vue.component('account-contracts', {
	props: {
		index: Number
	},
	data() {
		return {
			data: null,
			loading: false,
			contractFilter: [],
			contractFilterValues: []
		}
	},
	methods: {
		update() {
			this.loading = true;
			fetch('/wapi/wallet/contracts?index=' + this.index)
				.then(response => response.json())
				.then(data => {
					this.loading = false;
					this.data = data;
					this.contractFilter = Array.from(Array(data.length).keys())
					this.contractFilterValues = data.map(item => item.__type).filter((value, index, self) => self.indexOf(value) === index)
				});
		}
	},
	created() {
		this.update();
	},
	computed: {
		selectedContractFilterValues() {
			return this.contractFilterValues.filter((value, index, self) => this.contractFilter.some( i => i === index) );
		},
		filteredData() {
			if(this.data) {
				return this.data.filter( (item, index, self) => this.selectedContractFilterValues.some( r => item.__type == r) );
			}
			return null;
		}
	},
	template: `
		<v-card outlined color="transparent">
			<v-progress-linear  v-if="!data && loading" indeterminate absolute top></v-progress-linear>

			<v-chip-group column multiple v-model="contractFilter">
				<v-chip v-for="item in contractFilterValues" filter outlined>{{item}}</v-chip>
			</v-chip-group>

			<account-contract-summary v-if="filteredData" v-for="item in filteredData" :key="item.address" :index="index" :address="item.address" :contract="item">
			</account-contract-summary>
		</v-card>
		`
})

Vue.component('account-liquid', {
	props: {
		index: Number,
		limit: Number
	},
	data() {
		return {
			data: [],
			loading: true,
		}
	},
	computed: {
		headers() {
			return [
				{ text: this.$t('common.balance'), value: 'balance' },
				{ text: this.$t('common.symbol'), value: 'symbol' },
				{ text: this.$t('common.address'), value: 'address' },
				{ text: "", value: 'actions' },
			]
		}
	},
	methods: {
		update() {
			fetch('/wapi/wallet/swap/liquid?index=' + this.index)
				.then(response => response.json())
				.then(data => {
					this.loading = false;
					this.data = data;
				});
		},
	},
	created() {
		this.update()
	},
	template: `
		<div>
			<v-data-table
				:headers="headers"
				:items="data"
				:loading="loading"
				hide-default-footer
				disable-sort
				disable-pagination
				class="elevation-2"
			>
				<template v-slot:progress>
					<v-progress-linear indeterminate absolute top></v-progress-linear>
					<v-skeleton-loader type="table-row-divider@6" />
				</template>
				
				<template v-slot:item.balance="{ item }">
					<b>{{item.balance.value}}</b>
				</template>
				
				<template v-slot:item.symbol="{ item }">
					<template v-if="item.symbol != 'MMX'">
						<router-link :to="'/explore/address/' + item.currency">{{item.symbol}}</router-link>
					</template>
					<template v-else>
						{{item.symbol}}
					</template>
				</template>
				
				<template v-slot:item.address="{ item }">
					<router-link :to="'/swap/trade/' + item.address">{{item.address}}</router-link>
				</template>
				
				<template v-slot:item.actions="{ item }">
					<router-link :to="'/swap/liquid/' + item.address">
						<v-btn outlined>{{ $t('common.manage') }}</v-btn>
					</router-link>
				</template>
			</v-data-table>
		</div>
		`
})

Vue.component('account-details', {
	props: {
		index: Number
	},
	data() {
		return {
			account: null,
			addresses: null,
			keys: null
		}
	},
	methods: {
		update() {
			fetch('/wapi/wallet/account?index=' + this.index)
				.then(response => response.json())
				.then(data => {
					delete data.is_hidden;
					this.account = data;
				});
			fetch('/wapi/wallet/address?index=' + this.index + '&limit=1000')
				.then(response => response.json())
				.then(data => this.addresses = data);
			fetch('/wapi/wallet/keys?index=' + this.index)
				.then(response => response.json())
				.then(data => this.keys = data);
		},
		copyKeysToPlotter() {
			window.mmx.copyKeysToPlotter(JSON.stringify(this.keys))
		}
	},
	created() {
		this.update();
	},
	template: `
		<div>
			<object-table :data="account"></object-table>
			<object-table :data="keys" class="my-2"></object-table>

			<v-btn v-if="$isWinGUI && this.keys" @click="copyKeysToPlotter" color="primary">{{ $t('account_details.copy_keys_to_plotter') }}</v-btn>
			
			<v-simple-table>
				<thead>
					<tr>
						<th>Index</th><th>Address</th>
					</tr>
				</thead>
				<tbody>
					<tr v-for="(address, index) in addresses" :key="address">
						<td class="key-cell"><b>{{index}}</b></td>
						<td><router-link :to="'/explore/address/' + address">{{address}}</router-link></td>
					</tr>
				</tbody>
			</v-simple-table>
		</div>
		`
})

Vue.component('account-actions', {
	props: {
		index: Number
	},
	data() {
		return {
			account: null,
			seed: null,
			info: null,
			name: null,
			num_addresses: null,
			error: null,
			seed_dialog: false,
			remove_dialog: false
		}
	},
	methods: {
		update() {
			fetch('/wapi/wallet/account?index=' + this.index)
				.then(response => response.json())
				.then(data => {
					this.account = data;
					this.name = data.name;
					this.num_addresses = data.num_addresses;
				});
		},
		reset_cache() {
			const req = {};
			req.index = this.index;
			fetch('/api/wallet/reset_cache', {body: JSON.stringify(req), method: "post"})
				.then(res => this.on_response(res));
		},
		update_config() {
			if(this.num_addresses != this.account.num_addresses) {
				fetch('/api/wallet/set_address_count?index=' + this.index + "&count=" + this.num_addresses)
					.then(res => this.on_response(res));
			}
		},
		show_seed() {
			fetch('/wapi/wallet/seed?index=' + this.index)
				.then(response => response.json())
				.then(data => {
					this.seed = data;
					this.seed_dialog = true;
				});
		},
		remove() {
			fetch('/api/wallet/remove_account?index=' + this.index + "&account=" + this.account.index)
				.then(response => {
					if(response.ok) this.$router.push('/wallet/');
				});
		},
		on_response(res) {
			if(res.ok) {
				this.info = "Success";
				this.error = null;
			} else {
				res.text().then(data => {
					this.info = null;
					this.error = data;
				});
			}
		},
		copyToClipboard(value) {
			navigator.clipboard.writeText(value).then(() => {});
		}		
	},
	created() {
		this.update();
	},
	template: `
		<div>			
			<v-card>
				<v-card-text>
					<v-row>
						<v-col>
							<v-text-field
								v-model="name"
								:label="$t('create_wallet.account_name')"
								disabled>
							</v-text-field>
						</v-col>
						<v-col cols=4>
							<v-text-field
								v-model.number="num_addresses"
								:label="$t('create_wallet.number_of_addresses')"
								class="text-align-right">
							</v-text-field>
						</v-col>
					</v-row>
					
					<v-btn outlined @click="update_config">Update</v-btn>
					<v-btn outlined @click="reset_cache">{{ $t('account_actions.reset_cache') }}</v-btn>

					<v-dialog v-model="seed_dialog" max-width="800">
						<template v-slot:activator="{ on, attrs }">
							<v-btn outlined @click="show_seed">{{ $t('account_actions.show_seed') }}</v-btn>
						</template>
						<template v-slot:default="dialog">
							<v-card>
								<v-toolbar color="primary"></v-toolbar>
								<v-card-text class="pb-0">
									<v-container>
										<seed v-model="seed.string" readonly></seed>
										<v-text-field class="mt-2"
											v-if="account.with_passphrase"
											v-model="account.finger_print"
											label="Fingerprint (needed to verify passphrase)"
											readonly>
										</v-text-field>
									</v-container>
								</v-card-text>
								<v-card-actions>
									<v-spacer></v-spacer>
									<v-btn text @click="copyToClipboard(seed.string)">Copy</v-btn>
									<v-btn text @click="seed_dialog = false">Close</v-btn>
								</v-card-actions>
							</v-card>
						</template>
					</v-dialog>
					
					<v-dialog v-model="remove_dialog" max-width="800">
						<template v-slot:activator="{ on, attrs }">
							<v-btn v-if="index >= 100" outlined color="red" @click="remove_dialog = true">Remove</v-btn>
						</template>
						<template v-slot:default="dialog">
							<v-card>
								<v-toolbar color="primary"></v-toolbar>
								<v-card-text class="pb-0">
									<v-container>
										<v-alert border="left" colored-border type="warning" elevation="2">
											To recover any funds you will need to re-create the wallet from a stored backup!
										</v-alert>
										<v-alert border="left" colored-border type="info" elevation="2">
											'{{account.key_file}}' needs to be deleted manually.
										</v-alert>
									</v-container>
								</v-card-text>
								<v-card-actions class="justify-end">
									<v-btn color="error" @click="remove()">Remove</v-btn>
									<v-btn @click="remove_dialog = false">{{ $t('common.cancel') }}</v-btn>
								</v-card-actions>
							</v-card>
						</template>
					</v-dialog>
				</v-card-text>
			</v-card>

			<v-alert
				border="left"
				colored-border
				type="success"
				elevation="2"
				v-if="info"
				class="my-2"
			>
				{{info}}
			</v-alert>

			<v-alert
				border="left"
				colored-border
				type="error"
				elevation="2"
				v-if="error"
				class="my-2"
			>
				{{ $t('common.failed_with') }}: <b>{{error}}</b>
			</v-alert>
		</div>
		`
})

Vue.component('create-account', {
	props: {
		index: Number
	},
	data() {
		return {
			data: null,
			name: null,
			offset: null,
			num_addresses: 1,
			error: null
		}
	},
	methods: {
		update() {
			fetch('/wapi/wallet/account?index=' + this.index)
				.then(response => response.json())
				.then(data => this.data = data);
		},
		submit() {
			if(this.offset < 1) {
				this.error = "'Account Index' cannot be less than 1";
				return;
			}
			const req = {};
			req.config = {};
			req.config.name = this.name;
			req.config.index = this.offset;
			req.config.key_file = this.data.key_file;
			req.config.num_addresses = this.num_addresses;
			fetch('/api/wallet/create_account', {body: JSON.stringify(req), method: "post"})
				.then(response => {
					if(response.ok) {
						this.$router.push('/wallet/');
					} else {
						response.text().then(data => {
							this.error = data;
						});
					}
				});
		}
	},
	created() {
		this.update();
	},
	template: `
		<div>
			<v-card>
				<v-card-text>
					<v-row >
						<v-col>
							<v-text-field type="text" :label="$t('create_account.account_index')" v-model.number="offset" class="text-align-right"/>
						</v-col>
						<v-col cols="6">
							<v-text-field type="text" :label="$t('create_account.account_name')" v-model="name"/>
						</v-col>
						<v-col>
							<v-text-field type="text" :label="$t('create_account.number_of_addresses')" v-model.number="num_addresses"/>						
						</v-col>
					</v-row>
					<v-btn outlined @click="submit">{{ $t('create_account.create_account') }}</v-btn>
				</v-card-text>
			</v-card>

			<v-alert
				border="left"
				colored-border
				type="error"
				elevation="2"
				v-if="error"
				class="my-2"
			>
				{{ $t('common.failed_with') }}: <b>{{error}}</b>
			</v-alert>
		</div>
		`
})

Vue.component('create-wallet', {
	data() {
		return {
			name: null,
			num_addresses: 1,
			with_seed: false,
			with_passphrase: false,
			seed: null,
			passphrase: null,
			finger_print: null,
			error: null,
			show_passphrase: false
		}
	},
	methods: {
		submit() {
			const req = {};
			req.config = {};
			req.config.name = this.name;
			req.config.num_addresses = this.num_addresses;
			if(this.with_seed) {
				req.words = this.seed;
			}
			if(this.with_passphrase) {
				req.passphrase = this.passphrase;
			}
			fetch('/api/wallet/create_wallet', {body: JSON.stringify(req), method: "post"})
				.then(response => {
					if(response.ok) {
						this.$router.push('/wallet/');
					} else {
						response.text().then(data => {
							this.error = data;
						});
					}
				});
		},
		validate() {
			if(this.with_seed && this.with_passphrase && this.finger_print) {
				const req = {};
				req.words = this.seed;
				req.finger_print = this.finger_print;
				req.passphrase = this.passphrase;
				fetch('/wapi/passphrase/validate', {body: JSON.stringify(req), method: "post"})
					.then(response => {
						if(response.ok) {
							this.submit();
						} else {
							this.error = "Wrong passphrase!";
						}
					});
			} else {
				this.submit();
			}
		}
	},
	template: `
		<div>
			<v-card>
				<v-card-text>

					<v-row>
						<v-col>
							<v-text-field
								v-model="name"
								:label="$t('create_wallet.account_name')">
							</v-text-field>
						</v-col>
						<v-col cols=4>

							<v-text-field
								v-model.number="num_addresses"
								:label="$t('create_wallet.number_of_addresses')"
								class="text-align-right">
							</v-text-field>
						</v-col>
					</v-row>

					<v-checkbox
						v-model="with_seed"
						:label="$t('create_wallet.use_custom_seed')">
					</v-checkbox>

					<v-card v-if="with_seed">
						<v-card-title class="text-subtitle-1">
							{{$t('create_wallet.seed_words')}}
						</v-card-title>
						<v-card-text v-show="with_seed">
							<seed v-model="seed" :disabled="!with_seed"/>
						</v-card-text>
					</v-card>

					<v-checkbox
						v-model="with_passphrase"
						:label="$t('create_wallet.use_passphrase')">
					</v-checkbox>

					<v-card v-if="with_passphrase" class="pt-0">
						<v-card-text class="pt-2 pb-0">
							<v-text-field
								v-model="passphrase"
								:label="$t('create_wallet.passphrase')"
								:disabled="!with_passphrase"
								autocomplete="new-password"
								:type="show_passphrase ? 'text' : 'password'"
								:append-icon="show_passphrase ? 'mdi-eye' : 'mdi-eye-off'"
								@click:append="show_passphrase = !show_passphrase">
							</v-text-field>
							
							<v-text-field
								v-if="with_seed"
								v-model="finger_print"
								label="Fingerprint (optional, to validate passphrase)"
								placeholder="123456789">
							</v-text-field>
						</v-card-text>
					</v-card>
					
					<v-btn @click="validate()" class="mt-5" outlined color="primary">{{ $t('create_wallet.create_wallet') }}</v-btn>
				</v-card-text>
			</v-card>
							
			<v-alert
				border="left"
				colored-border
				type="error"
				v-if="error"
				elevation="2"
				class="my-2"
			>
				{{ $t('common.failed_with') }}: <b>{{error}}</b>
			</v-alert>
		</div>
		`
})

Vue.component('passphrase-dialog', {
	props: {
		show: Boolean
	},
	data() {
		return {
			passphrase: null,
			show_passphrase: false
		}
	},	
	model: {
		prop: 'show',
		event: 'close'
	},
	methods: {
		onSubmit() {
			this.$emit('submit', this.passphrase);
			this.passphrase = null;
			this.onClose();
		},
		onClose() {
			this.show = false
			this.$emit('close');
		}
	},	
	template: `
		<v-dialog v-model="show" max-width="800" persistent>
			<template v-slot:default="dialog">
				<v-card>
					<v-toolbar color="primary"></v-toolbar>
					<v-card-text class="pb-0 pt-2">
						<v-text-field
							v-model="passphrase"
							:label="$t('wallet_common.enter_passphrase')"
							required
							autocomplete="new-password"
							:type="show_passphrase ? 'text' : 'password'"
							:append-icon="show_passphrase ? 'mdi-eye' : 'mdi-eye-off'"
							@click:append="show_passphrase = !show_passphrase"							
							>
						</v-text-field>
					</v-card-text>
					<v-card-actions>
						<v-spacer></v-spacer>
						<v-btn text @click="onClose">Cancel</v-btn>
						<v-btn color="primary" text @click="onSubmit">Submit</v-btn>
					</v-card-actions>
				</v-card>
			</template>
		</v-dialog>
	`
})

Vue.component('account-send-form', {
	props: {
		index: Number,
		target_: String,		// fixed destination address (optional)
		source_: String,		// withdraw from contract (optional)
	},
	data() {
		return {
			accounts: [],
			balances: [],
			amount: null,
			target: null,
			source: null,
			memo: null,
			address: "",
			currency: null,
			fee_ratio: 1024,
			fee_amount: null,
			confirmed: false,
			result: null,
			error: null,
			passphrase_dialog: false
		}
	},
	methods: {
		update() {
			fetch('/wapi/wallet/accounts')
				.then(response => response.json())
				.then(data => this.accounts = data);
			if(this.source) {
				fetch('/wapi/address?id=' + this.source)
					.then(response => response.json())
					.then(data => this.balances = data.balances);
			} else {
				fetch('/wapi/wallet/balance?index=' + this.index)
					.then(response => response.json())
					.then(data => this.balances = data.balances);
			}
		},
		async is_locked() {
			return fetch('/api/wallet/is_locked?index=' + this.index).then(res => res.json());
		},
		async update_fee() {
			if(await this.is_locked() || !this.is_valid()) {
				this.fee_amount = "?";
				return;
			}
			const req = this.create_request();
			req.options.auto_send = false;
			
			fetch('/wapi/wallet/send', {body: JSON.stringify(req), method: "post"})
				.then(response => {
					if(response.ok) {
						response.json().then(tx => this.fee_amount = tx.exec_result.total_fee_value);
					} else {
						this.fee_amount = "?";
					}
				});
		},
		create_request() {
			const req = {options: {}};
			req.index = this.index;
			req.amount = this.amount;
			req.currency = this.currency;
			if(this.source) {
				req.src_addr = this.source;
			}
			req.dst_addr = this.target;
			req.options.memo = this.memo ? this.memo : null;
			req.options.fee_ratio = this.fee_ratio;
			return req;
		},
		async submit() {
			if(await this.is_locked()) {
				this.passphrase_dialog = true;
			} else {
				this.submit_ex(null);
			}
		},
		submit_ex(passphrase) {
			this.confirmed = false;
			if(!validate_address(this.target)) {
				this.error = "invalid destination address";
				return;
			}
			const req = this.create_request();
			req.options.passphrase = passphrase;
			
			fetch('/wapi/wallet/send', {body: JSON.stringify(req), method: "post"})
				.then(response => {
					if(response.ok) {
						response.json().then(data => this.result = data);
					} else {
						response.text().then(data => this.error = data);
					}
					this.update();
					this.$refs.balance.update();
					this.$refs.history.update();
				});
		},
		memo_rule(value) {
			if(value && value.length > 64) {
				return "maximum length is 64";
			}
			return true;
		},
		is_valid() {
			return this.target && this.currency && validate_amount(this.amount) == true;
		}
	},
	created() {
		if(this.source_) {
			this.source = this.source_;
		}
		if(this.target_) {
			this.address = "";
			this.target = this.target_;
		}
		this.update();
	},
	watch: {
		address(value) {
			if(value) {
				this.target = value;
			} else {
				this.target = null;
			}
			this.confirmed = false;
		},
		target() {
			this.confirmed = false;
		},
		currency() {
			this.confirmed = false;
		},
		amount() {
			this.confirmed = false;
		},
		memo() {
			this.confirmed = false;
		},
		fee_ratio() {
			if(this.confirmed) {
				this.update_fee();
			}
		},
		confirmed(value) {
			if(value) {
				this.update_fee();
			} else {
				this.fee_amount = null;
			}
		},
		result(value) {
			if(value) {
				this.error = null;
			}
		},
		error(value) {
			if(value) {
				this.result = null;
			}
		}
	},	
	computed: {
		selectAccounts() {
			var result = [];
			
			result.push({ text: this.$t('account_send_form.address_input'), value: ""});

			this.accounts.map(item => {
				result.push(
					{
						text: `${this.$t('account_send_form.wallet') } #${item.account} (${item.address})`,
						value: item.address
					}
				);
			});

			return result;
		}
	},
	template: `
		<div>
			<passphrase-dialog v-model="passphrase_dialog" @submit="p => submit_ex(p)"/>

			<balance-table :address="source" :show_empty="true" v-if="source" ref="balance"></balance-table>
			<account-balance :index="index" v-if="!source" ref="balance"></account-balance>

			<v-card class="my-2">
				<v-card-text>
					<v-text-field 
						v-if="!!source"
						v-model="source" 
						:label="$t('account_send_form.source_address')" disabled>
					</v-text-field>

					<v-select 
						v-model="address"
						:label="$t('account_send_form.destination')"
						:items="selectAccounts"
						item-text="text"
						item-value="value"
						:disabled="!!target_">
					</v-select>

					<v-text-field
						v-model="target"
						:label="$t('account_send_form.destination_address')"
						:disabled="!!address || !!target_"
						placeholder="mmx1..." clearable
					></v-text-field>

					<v-row>
						<v-col cols="3">
							<v-text-field class="text-align-right"
								:label="$t('account_send_form.amount')"
								v-model="amount"
								placeholder="1.23"
								:rules="[validate_amount]"
							></v-text-field>
						</v-col>
						<v-col>
							<v-select
								v-model="currency"
								:label="$t('account_send_form.currency')"
								:items="balances"
								item-text="contract"
								item-value="contract">

								<template v-for="slotName in ['item', 'selection']" v-slot:[slotName]="{ item }">
									{{item.symbol + (item.is_validated || source ? '' : '?')}}
									<template v-if="!item.is_native"> - [{{item.contract}}]</template>
								</template>

							</v-select>
						</v-col>
					</v-row>
					
					<v-text-field v-model="memo" label="Memo" :rules="[memo_rule]"" clearable></v-text-field>
					
					<v-row justify="end">
						<v-col cols="2">
							<tx-fee-select @update-value="value => this.fee_ratio = value"></tx-fee-select>
						</v-col>
						<v-col cols="2">
							<v-text-field class="text-align-right"
								label="TX Fee"
								v-model.number="fee_amount" suffix="MMX" disabled>
							</v-text-field>
						</v-col>
					</v-row>
					
					<v-card-actions class="py-0">
						<v-spacer></v-spacer>
						<v-switch v-model="confirmed" :label="$t('account_offer_form.confirm')" class="d-inline-block" style="margin-right: 50px"></v-switch>
						<v-btn @click="submit" outlined color="primary" :disabled="!this.confirmed || !is_valid()">{{ $t('account_send_form.send') }}</v-btn>
					</v-card-actions>
				</v-card-text>
			</v-card>

			<v-alert
				border="left"
				colored-border
				type="success"
				elevation="2"
				v-if="result"
				class="my-2"
			>
				{{ $t('common.transaction_has_been_sent') }}: <router-link :to="'/explore/transaction/' + result.id">{{result.id}}</router-link>
			</v-alert>

			<v-alert
				border="left"
				colored-border
				type="error"
				elevation="2"
				v-if="error"
				class="my-2"
			>
				{{ $t('common.failed_with') }}: <b>{{error}}</b>
			</v-alert>

			<account-tx-history :index="index" :limit="10" ref="history"></account-tx-history>
		</div>
		`
})

Vue.component('account-offer-form', {
	props: {
		index: Number
	},
	data() {
		return {
			tokens: [],
			balances: [],
			price: null,
			bid_amount: null,
			ask_symbol: null,
			bid_symbol: null,
			bid_currency: null,
			ask_currency: null,
			fee_ratio: 1024,
			fee_amount: null,
			confirmed: false,
			timer: null,
			result: null,
			error: null
		}
	},
	methods: {
		update() {
			fetch('/wapi/wallet/tokens')
				.then(response => response.json())
				.then(data => this.tokens = data);
			fetch('/wapi/wallet/balance?index=' + this.index)
				.then(response => response.json())
				.then(data => this.balances = data.balances);
		},
		update_fee() {
			if(this.is_valid()) {
				const req = this.create_request();
				req.options.auto_send = false;
				fetch('/wapi/wallet/make_offer', {body: JSON.stringify(req), method: "post"})
					.then(response => {
						if(response.ok) {
							response.json().then(tx => this.fee_amount = tx.exec_result.total_fee_value);
						} else {
							this.fee_amount = null;
						}
					});
			} else {
				this.fee_amount = null;
			}
		},
		create_request() {
			const req = {options: {}};
			req.index = this.index;
			req.bid = this.bid_amount;
			req.price = this.price;
			req.bid_currency = this.bid_currency.contract;
			req.ask_currency = this.ask_currency.currency;
			req.options.fee_ratio = this.fee_ratio;
			return req;
		},
		submit() {
			this.confirmed = false;
			fetch('/wapi/wallet/make_offer', {body: JSON.stringify(this.create_request()), method: "post"})
				.then(response => {
					if(response.ok) {
						response.json().then(data => this.result = data);
					} else {
						response.text().then(data => this.error = data);
					}
				});
		},
		is_valid() {
			return this.bid_currency && this.ask_currency
				&& validate_address(this.bid_currency.contract) && validate_address(this.ask_currency.currency)
				&& validate_amount(this.bid_amount) == true && this.price > 0;
		}
	},
	created() {
		this.update();
		this.timer = setInterval(() => { this.update(); }, 10000);
	},
	beforeDestroy() {
		clearInterval(this.timer);
	},
	watch: {
		price() {
			this.confirmed = false;
		},
		bid_amount() {
			this.confirmed = false;
		},
		ask_currency() {
			this.confirmed = false;
		},
		bid_currency() {
			this.confirmed = false;
		},
		fee_ratio() {
			this.update_fee();
		},
		confirmed(value) {
			if(value) {
				this.update_fee();
			}
		},
		result(value) {
			if(value) {
				this.error = null;
			}
		},
		error(value) {
			if(value) {
				this.result = null;
			}
		}
	},
	template: `
		<div>
			<account-balance :index="index" ref="balance"></account-balance>
			<v-card class="my-2">
				<v-card-text>
					<v-row>
						<v-col cols="4" class="pb-0">
							<v-text-field class="text-align-right"
								:label="$t('account_offer_form.offer_amount')"
								placeholder="1.23"
								v-model="bid_amount"
								:rules="[validate_amount]"
							></v-text-field>
						</v-col>
						<v-col class="pb-0">
							<v-select
								v-model="bid_currency"
								:label="$t('account_offer_form.offer_currency')"
								:items="balances">

								<template v-for="slotName in ['item', 'selection']" v-slot:[slotName]="{ item }">
									{{item.symbol + (item.is_validated ? '' : '?')}}
									<template v-if="!item.is_native"> - [{{item.contract}}]</template>
								</template>
							</v-select>
						</v-col>
					</v-row>
					<v-row>
						<v-col cols="4" class="py-0">
							<v-text-field class="text-align-right"
								:label="$t('account_offers.price')"
								v-model="price"
								:suffix="ask_currency && bid_currency ? bid_currency.symbol + ' / ' + ask_currency.symbol : null"
							></v-text-field>
						</v-col>
						<v-col class="py-0">
							<v-select
								v-model="ask_currency"
								label="Receive Currency"
								:items="tokens">

								<template v-for="slotName in ['item', 'selection']" v-slot:[slotName]="{ item }">
									{{item.symbol}}
									<template v-if="item.currency != MMX_ADDR"> - [{{item.currency}}]</template>
								</template>
							</v-select>
						</v-col>
					</v-row>
					<v-row justify="end">
						<v-col cols="2" class="py-0">
							<tx-fee-select @update-value="value => this.fee_ratio = value"></tx-fee-select>
						</v-col>
						<v-col cols="2" class="py-0">
							<v-text-field class="text-align-right"
								label="TX Fee"
								v-model.number="fee_amount" suffix="MMX" disabled>
							</v-text-field>
						</v-col>
					</v-row>
					<v-card-actions class="pb-0">
						<v-spacer></v-spacer>
						<v-switch v-model="confirmed" :label="$t('account_offer_form.confirm')" class="d-inline-block" style="margin-right: 50px"></v-switch>
						<v-btn @click="submit" outlined color="primary" :disabled="!this.confirmed || !is_valid()">{{ $t('account_offer_form.offer') }}</v-btn>
					</v-card-actions>
				</v-card-text>
			</v-card>
			
			<v-alert border="left" colored-border type="success" elevation="2" v-if="result" class="my-2">
				{{ $t('common.transaction_has_been_sent') }}: <router-link :to="'/explore/transaction/' + result.id">{{result.id}}</router-link>
			</v-alert>
			<v-alert border="left" colored-border type="error" elevation="2" v-if="error" class="my-2">
				{{ $t('common.failed_with') }}: <b>{{error}}</b>
			</v-alert>
			
			<account-offers :index="index" ref="offers"></account-offers>
		</div>
		`
})

Vue.component('account-offers', {
	props: {
		index: Number
	},
	data() {
		return {
			data: [],
			error: null,
			result: null,
			timer: null,
			state: true,
			dialog_item: null,
			dialog_cancel: false,
			dialog_deposit: false,
			dialog_withdraw: false,
			dialog_update: false,
			deposit_amount: null,
			new_price: null,
			fee_amount: null,
			request: null,
			request_url: null,
			canceled: new Set(),
			withdrawn: new Set()
		}
	},
	computed: {
		select_states() {
			return [
				{text: this.$t('account_offers.any'), value: false},
				{text: this.$t('account_offers.open'), value: true},
			];
		},
	},
	methods: {
		update() {
			fetch('/wapi/wallet/offers?index=' + this.index + '&state=' + this.state)
				.then(response => response.json())
				.then(data => this.data = data.sort((L, R) => R.height - L.height));
		},
		update_fee() {
			if(this.request) {
				const req = this.request;
				const url = this.request_url;
				req.options.auto_send = false;
				fetch(url, {body: JSON.stringify(req), method: "post"})
					.then(response => {
						if(response.ok) {
							response.json().then(tx => this.fee_amount = tx.exec_result.total_fee_value);
						} else {
							this.fee_amount = null;
						}
					});
			} else {
				this.fee_amount = null;
			}
		},
		update_fee_ratio(value) {
			if(this.request) {
				this.request.options.fee_ratio = value;
				this.update_fee();
			}
		},
		cancel(item) {
			const args = {options: {}};
			args.index = this.index;
			args.address = item.address;
			this.request = args;
			this.request_url = '/wapi/wallet/cancel_offer';
			this.update_fee();
			
			this.dialog_item = item;
			this.dialog_cancel = true;
		},
		withdraw(item) {
			const args = {options: {}};
			args.index = this.index;
			args.address = item.address;
			this.request = args;
			this.request_url = '/wapi/wallet/offer_withdraw';
			this.update_fee();
			
			this.dialog_item = item;
			this.dialog_withdraw = true;
		},
		deposit(item) {
			const args = {options: {}};
			args.index = this.index;
			args.currency = item.bid_currency;
			args.dst_addr = item.address;
			this.request = args;
			this.request_url = '/wapi/wallet/send';
			
			this.dialog_item = item;
			this.deposit_amount = null;
			this.dialog_deposit = true;
		},
		update_price(item) {
			const args = {options: {
				user: item.owner
			}};
			args.index = this.index;
			args.address = item.address;
			args.method = "set_price";
			args.args = [1];
			this.request = args;
			this.request_url = '/wapi/wallet/execute';
			this.update_fee();

			this.dialog_item = item;
			this.new_price = null;
			this.dialog_update = true;
		},
		submit() {
			const url = this.request_url;
			const item = this.dialog_item;
			const req = this.request;
			req.options.auto_send = true;
			fetch(url, {body: JSON.stringify(req), method: "post"})
				.then(response => {
					if(response.ok) {
						if(url == '/wapi/wallet/send') {
							this.canceled.delete(item.address);
						}
						if(url == '/wapi/wallet/cancel_offer') {
							this.canceled.add(item.address);
						}
						if(url == '/wapi/wallet/offer_withdraw') {
							this.withdrawn.add(item.address);
						}
						response.json().then(data => {
							this.result = data;
						});
					} else {
						response.text().then(data => this.error = data);
					}
				});
			this.dialog_cancel = false;
			this.dialog_withdraw = false;
			this.dialog_deposit = false;
			this.dialog_update = false;
			this.request = null;
			this.request_url = null;
			this.deposit_amount = null;
		}
	},
	watch: {
		state(value) {
			this.update();
		},
		index(value) {
			this.update();
		},
		deposit_amount(value) {
			if(this.request) {
				this.request.amount = value;
				this.update_fee();
			}
		},
		new_price(value) {
			if(this.request) {
				const new_price = value * Math.pow(2, 64) * Math.pow(10, this.dialog_item.bid_decimals - this.dialog_item.ask_decimals);
				this.request.args = [to_string_hex(new_price)];
				this.update_fee();
			}
		},
		result(value) {
			if(value) {
				this.error = null;
			}
		},
		error(value) {
			if(value) {
				this.result = null;
			}
		}
	},
	created() {
		this.update();
		this.timer = setInterval(() => { this.update(); }, 10000);
	},
	beforeDestroy() {
		clearInterval(this.timer);
	},
	template: `
		<div>
		<v-card class="my-2">
			<v-card-text>
				<v-select v-model="state" :label="$t('account_offers.status')"
					:items="select_states" item-text="text" item-value="value">
				</v-select>
			</v-card-text>
		</v-card>
		<v-card>
			<v-simple-table>
				<thead>
				<tr>
					<th colspan="2">{{ $t('account_offers.offering') }}</th>
					<th colspan="2">{{ $t('account_offers.received') }}</th>
					<th colspan="2">{{ $t('account_offers.price') }}</th>
					<th></th>
					<th></th>
				</tr>
				</thead>
				<tbody>
				<tr v-for="item in data" :key="item.address">
					<td class="collapsing"><b>{{item.bid_balance_value}}</b></td>
					<td>{{item.bid_symbol}}</td>
					<td class="collapsing"><b>{{item.ask_balance_value}}</b></td>
					<td>{{item.ask_symbol}}</td>
					<td class="collapsing"><b>{{parseFloat((1/item.display_price).toPrecision(6))}}</b></td>
					<td>{{item.bid_symbol}} / {{item.ask_symbol}}</td>
					<td><router-link :to="'/explore/address/' + item.address">TX</router-link></td>
					<td>
						<template v-if="item.bid_balance > 0 && !canceled.has(item.address)">
							<v-btn outlined text small color="red darken-1" @click="cancel(item)">{{ $t('account_offers.revoke') }}</v-btn>
						</template>
						<template v-if="item.ask_balance > 0 && !withdrawn.has(item.address)">
							<v-btn outlined text small @click="withdraw(item)">Withdraw</v-btn>
						</template>
						<v-btn outlined text small color="green darken-1" @click="deposit(item)">{{ $t('account_offers.deposit') }}</v-btn>
						<v-btn outlined text small color="blue darken-1" @click="update_price(item)">Update</v-btn>
					</td>
				</tr>
				</tbody>
			</v-simple-table>
		</v-card>
		
		<v-dialog v-model="dialog_cancel" max-width="1000">
			<template v-slot:default="dialog">
				<v-card>
					<v-toolbar color="primary"></v-toolbar>
					<v-card-title>{{ $t('account_offers.revoke') }} {{dialog_item.address}}</v-card-title>
					<v-card-text class="pb-0">
						<v-row justify="end">
							<v-col cols="3">
								<tx-fee-select @update-value="value => update_fee_ratio(value)"></tx-fee-select>
							</v-col>
							<v-col cols="3">
								<v-text-field class="text-align-right"
									label="TX Fee"
									v-model.number="fee_amount" suffix="MMX" disabled>
								</v-text-field>
							</v-col>
						</v-row>
					</v-card-text>
					<v-card-actions class="justify-end">
						<v-btn @click="submit()" color="primary">{{ $t('account_offers.revoke') }}</v-btn>
						<v-btn @click="dialog_cancel = false">{{ $t('common.cancel') }}</v-btn>
					</v-card-actions>
				</v-card>
			</template>
		</v-dialog>
		
		<v-dialog v-model="dialog_withdraw" max-width="1000">
			<template v-slot:default="dialog">
				<v-card>
					<v-toolbar color="primary"></v-toolbar>
					<v-card-title>Withdraw from {{dialog_item.address}}</v-card-title>
					<v-card-text class="pb-0">
						<v-row justify="end">
							<v-col cols="3">
								<tx-fee-select @update-value="value => update_fee_ratio(value)"></tx-fee-select>
							</v-col>
							<v-col cols="3">
								<v-text-field class="text-align-right"
									label="TX Fee"
									v-model.number="fee_amount" suffix="MMX" disabled>
								</v-text-field>
							</v-col>
						</v-row>
					</v-card-text>
					<v-card-actions class="justify-end">
						<v-btn @click="submit()" color="primary">Withdraw</v-btn>
						<v-btn @click="dialog_withdraw = false">{{ $t('common.cancel') }}</v-btn>
					</v-card-actions>
				</v-card>
			</template>
		</v-dialog>
		
		<v-dialog v-model="dialog_deposit" max-width="1000">
			<template v-slot:default="dialog">
				<v-card>
					<v-toolbar color="primary"></v-toolbar>
					<v-card-title>{{ $t('account_offers.deposit_to') }} {{dialog_item.address}}</v-card-title>
					<v-card-text class="pb-0">
						<v-text-field class="text-align-right"
							v-model="deposit_amount"
							:label="$t('common.amount')"
							:suffix="dialog_item.bid_symbol">
						</v-text-field>
						<v-row justify="end">
							<v-col cols="3">
								<tx-fee-select @update-value="value => update_fee_ratio(value)"></tx-fee-select>
							</v-col>
							<v-col cols="3">
								<v-text-field class="text-align-right"
									label="TX Fee"
									v-model.number="fee_amount" suffix="MMX" disabled>
								</v-text-field>
							</v-col>
						</v-row>
					</v-card-text>
					<v-card-actions class="justify-end">
						<v-btn @click="submit()" color="primary" :disabled="!(deposit_amount > 0)">{{ $t('common.deposit') }}</v-btn>
						<v-btn @click="dialog_deposit = false">{{ $t('common.cancel') }}</v-btn>
					</v-card-actions>
				</v-card>
			</template>
		</v-dialog>

		<v-dialog v-model="dialog_update" max-width="1000">
			<template v-slot:default="dialog">
				<v-card>
					<v-toolbar color="primary"></v-toolbar>
					<v-card-title>Update {{dialog_item.address}}</v-card-title>
					<v-card-text class="pb-0">
						<v-row justify="end">
							<v-col cols="4">
								<v-text-field class="text-align-right"
									v-model="new_price"
									label="New Price"
									:suffix="dialog_item.bid_symbol + ' / ' + dialog_item.ask_symbol">
								</v-text-field>
							</v-col>
							<v-col cols="3">
								<tx-fee-select @update-value="value => update_fee_ratio(value)"></tx-fee-select>
							</v-col>
							<v-col cols="3">
								<v-text-field class="text-align-right"
									label="TX Fee"
									v-model.number="fee_amount" suffix="MMX" disabled>
								</v-text-field>
							</v-col>
						</v-row>
					</v-card-text>
					<v-card-actions class="justify-end">
						<v-btn @click="submit()" color="primary" :disabled="!(new_price > 0)">Update</v-btn>
						<v-btn @click="dialog_update = false">{{ $t('common.cancel') }}</v-btn>
					</v-card-actions>
				</v-card>
			</template>
		</v-dialog>
		
		<v-alert border="left" colored-border type="success" elevation="2" v-if="result" class="my-2">
			{{ $t('common.transaction_has_been_sent') }}: <router-link :to="'/explore/transaction/' + result.id">{{result.id}}</router-link>
		</v-alert>

		<v-alert border="left" colored-border type="error" elevation="2" v-if="error" class="my-2">
			{{ $t('common.failed_with') }}: <b>{{error}}</b>
		</v-alert>
		</div>
		`
})

Vue.component('create-contract-menu', {
	props: {
		index: Number
	},
	data() {
		return {
			type: null,
			types: [
// 				{ value: "virtualplot", text: "mmx.contract.VirtualPlot" },
			]
		}
	},
	methods: {
		submit() {
			this.$router.push("/wallet/account/" + this.index + "/create/" + this.type);
		}
	},
	template: `
		<v-card>
			<v-card-text>
				<v-select v-model="type" :items="types" :label="$t('create_contract_menu.contract_type')">
				</v-select>
				<v-btn outlined @click="submit" :disabled="!type">{{ $t('common.create') }}</v-btn>
			</v-card-text>
		</v-card>
		`
})

Vue.component('create-locked-contract', {
	props: {
		index: Number
	},
	data() {
		return {
			owner: null,
			unlock_height: null,
			valid: false,
			confirmed: false,
			result: null,
			error: null
		}
	},
	methods: {
		check_valid() {
			this.valid = validate_address(this.owner) && this.unlock_height;
			if(!this.valid) {
				this.confirmed = false;
			}
		},
		submit() {
			// TODO
		},
		submit_ex(passphrase) {
			this.confirmed = false;
			const contract = {};
			contract.__type = "mmx.contract.Executable";
			// TODO
			contract.owner = this.owner;
			contract.unlock_height = this.unlock_height;
			const req = {};
			req.index = this.index;
			req.payload = contract;
			req.options = {passphrase: passphrase};
			fetch('/wapi/wallet/deploy', {body: JSON.stringify(req), method: "post"})
				.then(response => {
					if(response.ok) {
						response.json().then(data => this.result = data);
					} else {
						response.text().then(data => this.error = data);
					}
				});
		}
	},
	watch: {
		owner(value) {
			this.check_valid();
		},
		unlock_height(value) {
			this.check_valid();
		},
		result(value) {
			if(value) {
				this.error = null;
			}
		},
		error(value) {
			if(value) {
				this.result = null;
			}
		}
	},
	template: `
		<div>
			<v-chip label>{{ $t('common.create') }}</v-chip>
			<v-chip label>mmx.contract.TimeLock</v-chip>

			<v-card class="my-2">
				<v-card-text>
					<v-text-field 
						:label="$t('create_locked_contract.owner_address')"
						v-model="owner" 
						placeholder="mmx1...">
					</v-text-field>

					<v-text-field 
						:label="$t('create_locked_contract.unlock_height')"
						v-model.number="unlock_height">
					</v-text-field>

					<v-switch 
						v-model="confirmed"
						:disabled="!valid"
						:label="$t('common.confirm')"
						class="d-inline-block">
					</v-switch><br>

					<v-btn @click="submit" outlined color="primary" :disabled="!confirmed">{{ $t('common.deploy') }}</v-btn>

				</v-card-text>
			</v-card>

			<v-alert
				border="left"
				colored-border
				type="success"
				v-if="result"
				elevation="2"
				class="my-2"
			>
				{{ $t('common.deployed_as') }}: <b>{{result}}</b>
			</v-alert>

			<v-alert
				border="left"
				colored-border
				type="error"
				v-if="error"
				elevation="2"
				class="my-2"
			>
				{{ $t('common.failed_with') }}: <b>{{error}}</b>
			</v-alert>
		</div>
		`
})

Vue.component('create-plotnft', {
	props: {
		index: Number
	},
	data() {
		return {
			name: null,
			valid: false,
			fee_ratio: 1024,
			confirmed: false,
			result: null,
			error: null
		}
	},
	methods: {
		check_valid() {
			this.valid = this.name && this.name.length > 0;
			if(!this.valid) {
				this.confirmed = false;
			}
		},
		submit() {
			this.submit_ex(null);
		},
		submit_ex(passphrase) {
			this.confirmed = false;
			const req = {};
			req.index = this.index;
			req.name = this.name;
			req.options = {
				fee_ratio: this.fee_ratio,
				passphrase: passphrase
			};
			fetch('/api/wallet/plotnft_create', {body: JSON.stringify(req), method: "post"})
				.then(response => {
					if(response.ok) {
						this.result = this.name;
						this.name = null;
					} else {
						response.text().then(data => this.error = data);
					}
				});
		}
	},
	computed: {
		fee_amount() {
			return parseFloat((0.095 * this.fee_ratio / 1024).toFixed(3));
		}
	},
	watch: {
		name(value) {
			this.confirmed = false;
			this.check_valid();
		},
		result(value) {
			if(value) {
				this.error = null;
			}
		},
		error(value) {
			if(value) {
				this.result = null;
			}
		}
	},
	template: `
		<div>
			<v-card class="my-2">
				<v-card-text>
					<v-row>
						<v-col>
							<v-text-field
								label="New PlotNFT Name"
								v-model="name">
							</v-text-field>
						</v-col>
						<v-col cols="2">
							<tx-fee-select @update-value="value => this.fee_ratio = value"></tx-fee-select>
						</v-col>
						<v-col cols="2">
							<v-text-field class="text-align-right"
								label="TX Fee"
								v-model.number="fee_amount" suffix="MMX" disabled>
							</v-text-field>
						</v-col>
					</v-row>

					<v-card-actions class="py-0">
						<v-spacer></v-spacer>
						<v-switch 
							v-model="confirmed"
							:disabled="!valid"
							:label="$t('common.confirm')"
							class="d-inline-block" style="margin-right: 50px">
						</v-switch>
						<v-btn @click="submit" outlined color="primary" :disabled="!confirmed">{{ $t('common.create') }}</v-btn>
					</v-card-actions>
				</v-card-text>
			</v-card>

			<v-alert
				border="left"
				colored-border
				type="success"
				v-if="result"
				elevation="2"
				class="my-2"
			>
				Created new PlotNFT: {{result}}
			</v-alert>

			<v-alert
				border="left"
				colored-border
				type="error"
				v-if="error"
				elevation="2"
				class="my-2"
			>
				{{ $t('common.failed_with') }}: <b>{{error}}</b>
			</v-alert>
		</div>
		`
})

Vue.component('account-plotnfts', {
	props: {
		index: Number
	},
	data() {
		return {
			list: [],
			timer: null,
		}
	},
	methods: {
		update() {
			if(!this.$root.params) {
				setTimeout(() => { this.update(); }, 500);
				return;
			}
			fetch('/wapi/wallet/contracts?index=' + this.index + '&type_hash=' + this.$root.params.plot_nft_binary + '&owned=true')
				.then(response => response.json())
				.then(data => this.list = data);
		}
	},
	created() {
		this.update();
		timer = setInterval(() => { this.update(); }, 10000);
	},
	beforeDestroy() {
		clearInterval(this.timer);
	},
	template: `
		<div>
			<template v-for="item in list">
				<plotnft-control :address="item.address"></plotnft-control>
			</template>
		</div>
		`
})

Vue.component('plotnft-control', {
	props: {
		address: String
	},
	data() {
		return {
			data: null,
			timer: null,
		}
	},
	methods: {
		update() {
			fetch('/wapi/plotnft?id=' + this.address)
				.then(response => response.json())
				.then(data => this.data = data);
		}
	},
	created() {
		this.update();
		timer = setInterval(() => { this.update(); }, 10000);
	},
	beforeDestroy() {
		clearInterval(this.timer);
	},
	template: `
		<v-card v-if="data" class="my-2">
			<v-card-title>
				{{data.name}}
			</v-card-title>
			<v-card-text>
				<v-simple-table>
					<tbody>
					<tr>
						<td class="key-cell">Address</td>
						<td>
							{{data.address}}
							<template v-if="navigator.clipboard">
								<v-btn @click="navigator.clipboard.writeText(data.address)" text icon>
									<v-icon small class="pr-0">mdi-content-copy</v-icon>
								</btn>
							</template>
						</td>
					</tr>
					<tr>
						<td class="key-cell">Pool Server</td>
						<td v-if="data.server_url">{{data.server_url}}</td>
						<td v-else>N/A (solo farming)</td>
					</tr>
					<tr v-if="data.is_locked">
						<td class="key-cell">Unlock Height</td>
						<td>{{data.unlock_height}}</td>
					<tr>
					</tbody>
				</v-simple-table>
			</v-card-text>
		</v-card>
	`
});

Vue.component('wallet-menu', {
	data() {
		return {
			wallets: [],
			wallet: null,
			timer: null,
		}
	},
	emits: [
		"wallet-select"
	],
	methods: {
		update() {
			fetch('/wapi/wallet/accounts')
				.then(response => response.json())
				.then(data => {
					this.wallets = data;
					if(this.wallet == null && data.length) {
						this.wallet = data[0].account;
					}
				});
		}
	},
	watch: {
		wallet(value) {
			localStorage.setItem('active_wallet', value);
			this.$emit('wallet-select', value);
		}
	},
	created() {
		this.wallet = get_active_wallet();
		this.update();
		this.timer = setInterval(() => { this.update(); }, 60000);
	},
	beforeDestroy() {
		clearInterval(this.timer);
	},
	template: `
		<v-select
			v-model="wallet"
			:items="wallets"
			:label="$t('market_menu.wallet')"
			item-text="account"
			item-value="account">
			<template v-for="slotName in ['item', 'selection']" v-slot:[slotName]="{ item }">
				{{ $t('market_menu.wallet') }} #{{item.account}} ({{item.address}})
			</template>
		</v-select>
	`
})
